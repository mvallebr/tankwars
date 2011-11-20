/*
libgnow - a library to make games easily
Copyright (C) 1999  GamesNow team 

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.
		         
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

This library was made by GamesNow's stuff
Homepage: http://games_now.netpedia.net
Mailing list: gamesnow@egroup.com
*/

/*
Author of this file:
Marcelo Elias Del Valle - marceloelias@iname.com
Av. Patente , 193 bl. B22 apto. 17 
São Paulo - SP - Brazil
zip 04243-000						 
*/

#include <gnowSystemX.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/Xcms.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gnowconfigs.h>
#include <gnowColor.h>
#include <gnowDib.h>

TSystemX::TSystemX(char **aargv, int aargc) : TSystem(aargv, aargc){
	argv = aargv;
	argc = aargc;
	if (aargc>1)
		display = XOpenDisplay(aargv[1]);
	else
		display = XOpenDisplay(NULL);
	if (display==NULL) {
		printf("Não pude abrir o display!\n");
		return;
	}
	printf("Conexão com o display realizada!\n");
}


TSystemX::~TSystemX(){
	XCloseDisplay(display);
}

void TSystemX::ProcessEvents() {
	//Chama a função XNextEvents e chama os callbacks necessários, caso existam.
    XEvent event;
    KeySym key;

    while(XPending(display))
    {
        XNextEvent(display, &event);
        switch(event.type)
        {
            case KeyPress:
                key = XLookupKeysym(&event.xkey, 0);
		
                break;
	    case KeyRelease:
		key = XLookupKeysym(&event.xkey, 0);
		break;
            default:
            	break;
        };
    };
}

void TSystemX::set_palette_color(int indice, TColor color){  //Função ainda não implementada
	if (depth>8) return; //Setar de verdade a palette só tem sentido numa resolução de cores de até 8 bpp
	
}

void TSystemX::set_palette(TColor colors[256]){
	int i;
	virtual_screen->set_palette(colors);
	
   	XColor colors_x[256];

	if (depth==8){ //ajusta a palette para 8 bpp
   		for (i=0; i<256; i++) {
      			colors_x[i].pixel = i;
      			colors_x[i].flags = DoRed | DoGreen | DoBlue;
      			colors_x[i].red   = ((unsigned short) colors[i].red)   << 8 ;
      			colors_x[i].green = ((unsigned short) colors[i].green) << 8;
      			colors_x[i].blue  = ((unsigned short) colors[i].blue)  << 8;
   		}
		if (colormap)  XFreeColormap(display, colormap);

   		colormap = XCreateColormap (display,
                                     RootWindow    (display, screennum),
                                     DefaultVisual (display, screennum),
                                     AllocAll);
   		XStoreColors (display, colormap, colors_x, 256);
   		XSetWindowColormap (display, window, colormap);
   		return;
	}
}

void TSystemX::open_real_screen(char* title){
	swidth = DEF_WIDTH;
	sheight = DEF_HEIGHT;
	printf("Resolução de pontos: %dx%d\n", swidth, sheight);

	colormap = 0;	

	screennum = DefaultScreen(display);
	screenptr = DefaultScreenOfDisplay(display);
	visual    = DefaultVisualOfScreen(screenptr);
	 //Resolução de cores
	depth = DefaultDepth(display, screennum);
	printf ("Resolução de cores: %i \n", depth);
	//Suporta nossa resolução?
	if (depth < DEF_COLOR){
		printf("Este programa precisa de uma profundidade de cores de no mínimo %d bbp para rodar!\n", DEF_COLOR);
		return ;
	}

	printf("depth = %d \n", depth);
	virtual_screen = new TDib(depth);
	
	
	//Determina o tamanho de cada pixel em bytes, ou seja, o número de bytes
	//necessários para armazenar a cor de um determinado ponto na tela
	switch (depth){
	case 8:
		pixelsize = 1;
		break;
	case 16:
		pixelsize = 2;
		break;
	case 24:
		pixelsize = 4;
		break;
	default:
		pixelsize = 1;
		break;
	}

 	//Cria efetivamente a janela
   	//Execute "man XCreateWindow" para maiores detalhes
   	window = XCreateWindow(display,
                              //janela pai
                              RootWindowOfScreen(screenptr),
                              //Coordenada X
                  (DisplayWidth(display, screennum) - (swidth))/2,
                              //Coordenada Y
                  (DisplayHeight(display, screennum) - (sheight))/2,
                              swidth,   //Largura
                              sheight,  //Altura
                              0,           //largura da borda
                              depth,   //Resolução de cores
                              InputOutput, //Classe da janela
                              visual,  //Tipo de visual da janela (acho)
                              0,           //Não vamos usar nehum atributo
                              NULL         //adicional
                              );
   	//Agora precisamos avisar ao gerenciador de janelas sobre a nossa janela
   	//Basicamente, passamos as propriedades retangulares, isto é, o retângulo
   	//que a janela ocupa 
   	//Essa parte não é completamente necessária, mas pode ajudar
     	{//Novo escopo
        	XSizeHints Hints; //Dicas pro gerenciador de jnelas
        	Hints.flags = PSize | PMinSize | PMaxSize; //Dicas que vamos passar
        	Hints.min_width = Hints.max_width = Hints.base_width = swidth;
        	Hints.min_height= Hints.max_height= Hints.base_height= sheight;
        	XSetWMNormalHints (display, window, &Hints);
        	//Agora ajustamos o título da janela
        	XStoreName (display, window, title);
     	}
	
	//Pede para o X mandar mensagens sobre os eventos desejados
   	XSelectInput (display, window,
        	ExposureMask|KeyPressMask|KeyReleaseMask|ButtonPressMask);
   	//Cria um contexto gráfico para a janela
   	gc = XCreateGC (display, window, 0, NULL);

   	//Mapeia a janela
   	XMapRaised(display, window);

   	/**********************************************************************/
   	//hora de carregar as imagens e ajustar a palette

   	/*Criacao do buffer para Page Flipping */
   	//Tamanho do buffer 
   	screensize = swidth * sheight * pixelsize;
   	//Aloca o bitmap
   	virtual_screen->set_size(swidth, sheight); 
	vs_alloc = 1;
   	if (! virtual_screen->is_loaded()) {
      		printf("Lamento, mas não consegui alocar memória suficiente!\n");
      		return ;
   	}
   	//Faz o X entender o buffer como uma imagem
   	ximage = XCreateImage (display, visual, depth,
                              ZPixmap, //Formato bitmap padrao
                              0,       //Número de pixels ignorados no início
                              virtual_screen->get_buffer(), //O buffer
                              swidth,         //Largura
                              sheight,        //Altura
                              32,                //bitmap-pad. Veja a man page
                              swidth * pixelsize //Bytes por linha
                              );
   	if (! ximage) {
      		printf ("Erro ao criar a imagem!\n");
      		return ;
   	}

	refresh();
	//Exibe tudo
   	XFlush(display);
}

void TSystemX::close_real_screen(){
	 //Termina a conexão com o XServer e sai do programa
   	if (ximage)
     		XDestroyImage(ximage);
	if (colormap)  
		XFreeColormap(display, colormap);
	vs_alloc =0;
   	XFreeGC (display, gc);
   	XDestroyWindow (display, window);
}










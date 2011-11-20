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

#ifndef SYSTEMX_H
#define SYSTEMX_H

#include "gnowSystem.h" 
#include "gnowColor.h"
#include "gnowDib.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/Xcms.h>
#include <stdio.h>

class TSystemX : public TSystem { 
 private: //Declarações privadas
	Display* display;	
	Visual* visual;
	Screen* screenptr;
	Window window;
	GC gc;
	XImage* ximage;		      
	int screennum;                //Numero da tela, para o X
	int pixelsize;		      //Depende da profundidade de cores
	int screensize;               //Tamanho da tela virtual (width*height)
	Colormap colormap; //palette, para o X

 protected: //Declarações protegidas

	//Override de algumas funções da classe base
	void open_real_screen(char* title);
	void close_real_screen();
	int swidth, sheight;

 public: //Declarações públicas

	TSystemX(char **aargv, int aargc); //Construtor
	~TSystemX(); //Destrutor
	
	//Override de algumas funções da classe base
	void ProcessEvents();
	void set_palette_color(int indice, TColor color);
	void set_palette(TColor colors[256]);


	inline void TSystemX::refresh(){
        	//Exibe a imagem
        	XPutImage (display, window, gc, ximage,
              		0, 0, //src_x,  src_y
              		0, 0, //dest_x, dest_y
              		virtual_screen->get_width(), virtual_screen->get_height() //largura e altura
              		);//Exibe a imagem
	}
};

#endif // SYSTEMX_H






















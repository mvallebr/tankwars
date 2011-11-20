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

#include <gnowDib.h>
#include <stdio.h> 
#include <stdlib.h>

TDib::TDib(int ndepth){ //Construtor
	inicializa (ndepth);
}

void TDib::inicializa (int ndepth) {
	depth = ndepth;
	
	switch (depth) {
		case 16:
			pixel_size = 2;
			break;
		case 24:
		case 32:
			pixel_size = 4;
			break;
		default: //8 bpp
			pixel_size = 1;
			break;
	}

	loaded=0;
	filename[255]=0;
}

TDib::TDib(int ndepth, char* nfilename){ //Construtor
	inicializa (depth);
	LoadFromPcx(nfilename);
}

void TDib::set_palette(TColor npalette[256]){
	for(int i=0; i<256; i++)
		palette[i]=npalette[i];
}


TDib::~TDib(){ //Destrutor
	free_buffer();
}

int TDib::LoadFromPcx(char* nfilename){
	strcpy(filename, nfilename);
	read_palette();
	read_buffer();
	return 1;
}

int TDib::read_palette(){
	FILE *f;
   	int i;
   	f = fopen (filename, "rb");
   	if (!f) return 0;
   	fseek(f, -768L, SEEK_END); //Posiciona o carro no inicio da palette

   	for (i=0; i<256; i++) {  //Le a palette do arquivo
      		palette[i].red   = (unsigned char) (getc(f) );
      		palette[i].green = (unsigned char) (getc(f) );
      		palette[i].blue  = (unsigned char) (getc(f) );
   	}

   	fclose(f);
   	return 1;
}

int TDib::read_buffer(){
	FILE *f;
   	int tamanho; //Tamanho em bytes do buffer
   	int i;
   	unsigned char clido, numbytes;

   	f = fopen(filename, "rb");
   	if (!f) return 0;

   	//Lê o header e aloca o buffer
   	fread(&header, sizeof(pcx_header), 1, f);
   	width  = header.width+1;
   	height = header.height+1;
   	tamanho = (header.width+1) * (header.height+1);
   	printf("%s, largura: %d altura: %d tamanho: %d \n",
        	filename, header.width+1, header.height+1, tamanho);
	set_size (header.width +1, header.height+1);
   	if (!(buffer)) return 0;
   	//Lê a imagem
   	i=0;
   	while (i<tamanho){
      		clido = (unsigned char) getc(f);
      		if (clido > 191) { //É um RLE?
         		numbytes = clido - 192;
         		clido = (unsigned char) getc(f);
         		while (numbytes>0){
				add_pixel(clido, i);
				i++;
            			numbytes = numbytes - 1;
         		}
      		}
      		else {
			add_pixel(clido, i);
			i++;
		}
   	}
   	fclose(f);
   	return 1;
}


void TDib::set_size(int nwidth, int nheight) {
	int tamanho;

	free_buffer();
	width = nwidth; height = nheight;
	tamanho = pixel_size * (nwidth) * (nheight);
   	buffer = new char [ tamanho ];
	loaded = (buffer==NULL) ? 0 : 1;
}

void TDib::free_buffer(){
	if (loaded && (buffer!=NULL)) delete buffer;
}















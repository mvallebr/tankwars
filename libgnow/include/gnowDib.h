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

#ifndef DIB_H
#define DIB_H

#include "gnowColor.h"
#include <stdio.h>

typedef struct pcx_header
{
        char manufacturer;
        char version;
        char encoding;
        char bits_per_pixel;
        short x,y;
        short width,height;
        short horz_res;
        short vert_res;
        char ega_palette[48];
        char reserved;
        char num_color_planes;
        short bytes_per_line;
        short palette_type;
        char padding[58];
} pcx_header;

class TDib { 
 private: //Declarações privadas
	int loaded;
 protected: //Declarações protegidas
	char filename[256];
	char* buffer;
	pcx_header header;
	int width, height;
	int depth;
	int pixel_size;
	int read_buffer();
	int read_palette();

 public: //Declarações públicas
	TColor palette[256]; //Deveria ser encapsulado, mas assim é mais agradável pra mim e não acho que haja necessidade nesse caso.

 	TDib(int ndepth, char* nfilename);
	TDib(int ndepth);
	void inicializa(int ndepth);
	~TDib();	
	int LoadFromPcx(char* nfilename);
	inline int get_width()  { return width; }	
	inline int get_height() { return height; }	
	inline int get_depth()  { return depth; }
	void set_size  (int nwidth, int nheight);	//Altera o tamanho do buffer, mas apagam o buffer atual

	inline char* get_buffer() { return buffer; }
	inline int is_loaded(){ return loaded; }
	void free_buffer();

	void set_palette(TColor npalette[256]);
	inline void put_dib (TDib& dib, int x, int y ){
                register int  j, w, h;
                char* dbuffer;

                w = ((width-x) <dib.get_width())  ? width-x  : dib.get_width();
                h = ((height-y)<dib.get_height()) ? height-y : dib.get_height();
                dbuffer = dib.get_buffer();

		switch(pixel_size) {
			case 1:
                		for(j=0; j<h; j++)
                        		memcpy(buffer+(j+y)*width+x, dbuffer+j*dib.get_width(), w);
				break;
			case 2:
				h+=h; w+=w;
				x*=2; y*=2;
                		for(j=0; j<h; j+=2)
                        		memcpy(buffer+((j+y)*width+x), dbuffer+(j*dib.get_width()), w);
				break;
			case 4:
				h*=4; w*=4;
				x*=4; y*=4;
                		for(j=0; j<h; j+=4)
                        		memcpy(buffer+((j+y)*width+x), dbuffer+(j*dib.get_width()), w);
				break;
		}
        }
        inline void put_dib_mask (TDib& dib, int x, int y, char mask ){

                     	register int i, j, w, h;
                     	int tam, add, base;
                     	char* dbuffer;
			
		     	switch(depth) {
				case 8:
					tam = width;
                                        dbuffer = dib.get_buffer();
                                        w = dib.get_width();
                                        h = dib.get_height();
                                        add = y*tam+x;
                                        base= 0;
                                        for(j=0; j<h; j++, add+=tam-w)
                                                for(i=0; i<w; i+=1) {
                                                        if(dbuffer[base]!= mask){
                                                                buffer[add]=dbuffer[base];
                                                        }
                                                        base++; add++;
                                                }

					break;
				case 16:
					char a, b;
					tam = 2*width;
					x+=x; 
                                        dbuffer = dib.get_buffer();
                                        w = 2*dib.get_width();
                                        h = 2*dib.get_height();
                                        add = y*tam+x;
                                        base= 0;
                                        for(j=0; j<h; j+=2, add+=tam-w)
                                                for(i=0; i<w; i+=2) {
							a = ((palette[mask].blue>>3) & 31)    | ((palette[mask].green & 56) << 2) | 128;//128 = brilho
							b = ((palette[mask].red & 240) >> 1)  | ((palette[mask].green & 192) >> 6) ;
                                                        if((dbuffer[base]!=a) && (dbuffer[base+1]!=b)){
                                                                buffer[add]=    dbuffer[base]; 
								buffer[add+1]=  dbuffer[base+1]; 
                                                        }
                                                        base+=2; add+=2;
                                                }
					break;
				case 24: case 32:
                     			tam = 4*width;
                     			dbuffer = dib.get_buffer();
					x*=4; 
                     			w = 4*dib.get_width();
                     			h = 4*dib.get_height();
                     			add = y*tam+x;
                     			base= 0;
                     			for(j=0; j<h; j+=4, add+=tam-w)
                       				for(i=0; i<w; i+=4) {
                         				if((dbuffer[base+1]!=palette[mask].red) && (dbuffer[base+2]!=palette[mask].green) && 
												   (dbuffer[base+3]!=palette[mask].blue) ){
				 				buffer[add+1]=dbuffer[base+1];
				 				buffer[add+2]=dbuffer[base+2];
				 				buffer[add+3]=dbuffer[base+3];
			 				}
                         				base+=4; add+=4;
                       				}
					break;
			}
        }

        inline void tile (TDib& dib){
                register int i, j;
                for(i=0; i< ((int)(width / dib.get_width()))+1; i++)
                   for(j=0; j< ((int)(height/dib.get_height()))+1; j++)
                        put_dib(dib, i*dib.get_width(), j*dib.get_height());

        }

        inline void pset(int x, int y, char indice){//Adiciona um pixel no buffer
		add_pixel(indice, y*width + x);	
        }
	
	inline void add_pixel(unsigned char clido, int num_pixel) { //Mais rápido que o pset...
                if (!loaded) return;
        	switch( depth) {
                	case 8:
                        	buffer[num_pixel]=clido;
                        	break;
                	case 16:
                        	buffer[num_pixel*2] =   ((palette[clido].blue>>3) & 31)    | ((palette[clido].green & 56) << 2) | 128; //128 = brilho
                        	buffer[num_pixel*2+1]=  ((palette[clido].red & 240) >> 1)  | ((palette[clido].green & 192) >> 6) ;
                        	break;
                	case 24: case 32:
                        	buffer[num_pixel*4+1] = palette[clido].red;
                        	buffer[num_pixel*4+2] = palette[clido].green;
                        	buffer[num_pixel*4+3] = palette[clido].blue;
                        	break;
                	default:
                        	buffer[num_pixel]=0;
        	}
	}
};

#endif // DIB_H


























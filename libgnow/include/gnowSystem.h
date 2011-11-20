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


#ifndef SYSTEM_H
#define SYSTEM_H
#include "gnowColor.h"
#include "gnowDib.h"
#include <string.h>


class TSystem { 
 private: //Declarações privadas

 protected: //Declarações protegidas
	char **argv;
	int argc;
	int num_screens; //Número de telas abertas no momento.
	TColor palette[256];	

		//Funções que devem sofrer override
	virtual void open_real_screen(char* title) =0 ;
	virtual void close_real_screen() ;
	int depth;                    //Resolucao de cores (profundidade)  
	int vs_alloc;  //Tela virtual já foi alocada???
 public: //Declarações públicas
	TSystem(char **aargv, int aargc);
	virtual ~TSystem();
	


	TDib* virtual_screen;

	void close_last_screen();

		//Funções que devem sofrer override
	virtual void ProcessEvents()=0;
	void new_screen(char* title);
	virtual void refresh() = 0 ;      //Atualiza a tela com o buffer (page_flipping)
	virtual void set_palette(TColor colors[256]) = 0;
	virtual void set_palette_color(int indice, TColor color) = 0;
	TColor get_palette_color(int indice);
	inline int get_depth() { return depth; }

};

#endif // SYSTEM_H

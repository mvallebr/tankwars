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

#include <gnowSystem.h>
#include <stdio.h>

TSystem::TSystem(char **aargv, int aargc) { //Construtor
	argv = aargv;
	argc = aargc;

	num_screens = 0; 
	vs_alloc=0;
}

TSystem::~TSystem(){
	if (num_screens>0) close_real_screen();
}

void TSystem::new_screen(char* title) {
  	if (num_screens<=0)
                open_real_screen(title);
        num_screens++;
}

void TSystem::close_last_screen(){
	if (num_screens<= 0) return;
	num_screens--;

	if (num_screens<= 0)
		close_real_screen(); 
}



TColor TSystem::get_palette_color(int indice){
	return palette[indice];
}

void TSystem::close_real_screen(){
	printf("Nunca passo aqui...");
}






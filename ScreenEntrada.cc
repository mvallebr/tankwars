/*
Marcelus TankWars - A simple game that uses libgnow
Copyright (C) 1999  Marcelo Elias Del Valle 

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

Marcelo Elias Del Valle - marceloelias@iname.com
Av. Patente , 193 bl. B22 apto. 17 
São Paulo - SP - Brazil
zip 04243-000						 
*/

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "ScreenEntrada.h"
#include "configs.h"

#include <gnowScreen.h> 
#include <gnowDib.h>
#include <gnowSystem.h> 

//#include <gnowconfigs.h>

TScreenEntrada::TScreenEntrada(TSystem &newsystem, char** argv, int argc) : 
	TScreen(newsystem, argv, argc){
}


int TScreenEntrada::Show() {

	int i, j;
	char nome_arq01[256], nome_arq02[256];;
	TColor cores[256];
	TDib dib01(system->get_depth()), dib02(system->get_depth());
	
	for(i=0; i<256; i++){
		cores[i].red   = 0;
		cores[i].green = 0;
		cores[i].blue  = i;
	}
	system->set_palette(cores);

	for(i=0; i<width; i++)
		for(j=0; j<height; j++)
			system->virtual_screen->pset(i, j, j%255);

	system->refresh();
	sleep(1);
	
	/*	
	for(u=0; u<256+4; u+=4){
        	for(i=0; i<width; i++)
                	for(j=0; j<height; j++)
                        	system->virtual_screen->pset(i, j, j+u%255);
		system->refresh();
        }
	sleep(3);
	*/

	strcpy(nome_arq01, DIR_IMAGES);
	strcat(nome_arq01, "fundo.pcx");
	dib01.LoadFromPcx(nome_arq01);

	strcpy(nome_arq02, DIR_IMAGES);
        strcat(nome_arq02, "pedra.pcx");
        dib02.LoadFromPcx(nome_arq02);


	system->set_palette( dib01.palette );
	system->virtual_screen->put_dib( dib01, 10, 10 );
	system->refresh();

	sleep(1);
	
	system->virtual_screen->tile(dib01);
        system->refresh();

        
	sleep(1);
	time_t tempo1,tempo2;
	time(&tempo1);

	for(int freq=0; freq<10; freq++){
		i = (system->virtual_screen->get_width()-dib02.get_width())/2;
		for(j=0; j< system->virtual_screen->get_height()-dib02.get_height(); j+=15) {	
			system->virtual_screen->tile(dib01);
			system->virtual_screen->put_dib_mask( dib02, i, j, 0 );
        		system->refresh();
			system->ProcessEvents();
		}
	}
	time(&tempo2);

	printf("Tempo decorrido: %ld s\n",tempo2-tempo1);
        sleep(1);
	return 0;
}

















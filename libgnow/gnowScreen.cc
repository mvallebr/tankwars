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

#include <gnowScreen.h>
#include <gnowSystem.h>
#include <gnowSystemX.h>
#include <stdio.h>
#include <unistd.h>

TScreen::TScreen(TSystem &newsystem, char** argv, int argc){ 
	system = &newsystem;	
	system->new_screen("libGNow");
	width  = system->virtual_screen->get_width();
	height = system->virtual_screen->get_height();
}


int TScreen::Show(){
	sleep(1);
	return 0;
}

TScreen::~TScreen(){ //Destrutor
	system->close_last_screen();
}

void TScreen::on_key_press(long keycode) {
	printf("Pressionada a tecla %ld\n", keycode);
}

void TScreen::on_key_up   (long keycode) {
	printf("Solta a tecla %ld\n", keycode);
}






















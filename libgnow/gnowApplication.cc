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

#include <gnowApplication.h>
#include <gnowSystem.h>
#include <gnowSystemX.h>
#include <gnowScreen.h> 
#include <gnowconfigs.h>
#include <stdio.h>

TApplication::TApplication(char** aargv, int aargc) : system(aargv, aargc){
        argv = aargv;
        argc = aargc;
}


void TApplication::Run(){
	TScreen* scr1=0;
	int proxima_tela=1;
	
	do{
		switch (proxima_tela){
			case 1:
				scr1 = new TScreen(system, argv, argc);
				break;
			default:
				break;
		}	
			
		proxima_tela = scr1->Show();
		delete scr1;	
	} while (proxima_tela!=0);

}



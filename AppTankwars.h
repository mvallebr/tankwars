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

#ifndef APPTANKWARS_H
#define APPTANKWARS_H

#include <gnowApplication.h>
#include <stdio.h> 

class TAppTankwars : public TApplication { 
 private: //Declarações privadas
 protected: //Declarações protegidas

 public: //Declarações públicas
	void Run();
	TAppTankwars (char **argv, int argc) : TApplication(argv, argc) { printf("Acho"); }
	virtual ~TAppTankwars() { }
};

#endif // APPTANKWARS_H

/*
libgnow - a library to make games easily
Copyright (C) 1999 GamesNow team 

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

#ifndef EVENT_H
#define EVENT_H

#include <string.h>

class TEvent { 
 private: //Declarações privadas
	typedef void (TEvent::*TMemberFunction) ();
	union
	{
		const void *Callback;
		char CallbackMember [sizeof (TMemberFunction)];
	};
	void* Class;

 protected: //Declarações protegidas
 public: //Declarações públicas
	TEvent () {
		Class    =0;
		Callback =0;
	}
	TEvent (const void *_Class, const void (*_Callback) )
	{
		Class=0;
		if (_Class)  // Callback must be a member
		{
			Class = (void*)_Class;
			memcpy (CallbackMember, _Callback, sizeof(TMemberFunction));
		}
		else  // Must be a regular pointer to a function
			Callback = _Callback;
	}
	inline void SetCallBack(const void* _Callback){
		Callback = _Callback;
	}
	inline void process(){
		(Class->*Callback)();
	}
};

#endif // EVENT_H




















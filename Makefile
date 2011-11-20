#Tankwars Makefile
# digite make para compilar o seu tankwars

CXX=egcs #g++
LIBGNOWDIR=./libgnow
CXXFLAGS=-Wall -O6 -g -I$(LIBGNOWDIR)/include 
LIBS= -L/usr/X11R6/lib -lX11 -L$(LIBGNOWDIR) -lgnow 
OBJECTS=main.o ScreenEntrada.o AppTankwars.o #gnowApplication.o gnowColor.o gnowDib.o gnowScreen.o gnowSystem.o gnowSystemX.o
PROGRAM=tank

all: 
	less README

tank:  $(OBJECTS)
	$(CXX) $(LIBS) $(OBJECTS) -o $(PROGRAM)
gnowlib: 
	cd $(LIBGNOWDIR) && make x11 && make install && ldconfig && make clean

clean:
	rm -rf *.o $(PROGRAM) core

build: clean all
roda: build 
	$(PROGRAM)

# libGnow Make file
# Para instalar a lib, digite 'make PLATAFORMA && make install',
# onde PLATAFORMA pode ser umas das op��es seguintes:
# x11  - XWindow
# svga - SvgaLib
# dos  - Argh!!!

MAJORVERSION=0
MINORVERSION=01
CXX=egcs #g++
INCLUDEDIR=./include
CXXFLAGS=-Wall -O6 -g -I$(INCLUDEDIR) -fPIC 
LIBNAME=libgnow.so
LIBS= -L/usr/X11R6/lib -lX11 -shared -Wl,-soname,$(LIBNAME).$(MAJORVERSION) 
OBJECTSX11=gnowSystemX.o 
OBJECTS=gnowApplication.o gnowScreen.o gnowSystem.o gnowColor.o gnowDib.o 
PREFIXDIR=/usr

all:  
	less README

x11: $(OBJECTS) $(OBJECTSX11)
	$(CXX) $(LIBS) -o $(LIBNAME).$(MAJORVERSION).$(MINORVERSION) $(OBJECTS) $(OBJECTSX11)
	ln -fs $(LIBNAME).$(MAJORVERSION).$(MINORVERSION)  $(LIBNAME).$(MAJORVERSION)
	ln -fs $(LIBNAME).$(MAJORVERSION)   $(LIBNAME) 

svga: 
	@echo "Ainda n�o implementado!"

dos:
	@echo "Ainda estamos sem tempo para perdermos com porcarias..."

clean:
	rm -rf *.o  core

install:
	@echo
	cp $(INCLUDEDIR)/* $(PREFIXDIR)/include/
	cp ./$(LIBNAME)* $(PREFIXDIR)/lib/
	@echo "Adicione a linha '$(PREFIXDIR)/lib'"
	@echo "no seu arquivo '/etc/ld.so.conf' e"
	@echo "ent�o rode ldconfig (como root, � claro)."
	@echo
uninstall:
	@echo
	@echo Desintalando a lib do diret�rio $(PREFIXDIR)
	rm -f $(PREFIXDIR)/lib/$(LIBNAME)*
	rm -f $(PREFIXDIR)/include/gnow*.h

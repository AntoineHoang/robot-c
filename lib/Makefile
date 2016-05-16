##-----------------------------------------------------------------------##
#
# 	Titre: Makefile principal
# 
#	Auteurs: Bartholomew Chwalek
#
#
#	Description:
#
#
##-----------------------------------------------------------------------##

##------------------------Variables--------------------------------------##

include ../src/ATMega16Defs

CC=avr-gcc
CFLAGS=-mmcu=atmega16 -Wall -Os  -std=c++0x  #-Werror
AR=avr-ar
ARFLAGS=-crs
CPP = can.cpp ajusterPWM.cpp memoire_24.cpp del.cpp midi.cpp detecteurligne.cpp
H = FonctionGlobales.h can.h memoire_24.h del.h midi.h detecteurligne.h
DL = ------------ 
NOMPROJET = Librairie pour projet Robot inf1995.
CIBLE = libATMega16.a
REMOVE = rm -f
EDITOR = kate

##-----------------------------------------------------------------------##


all : $(CPP:.cpp=.o)
	-@echo $(DL) $(NOMPROJET)
	-@echo $(DL) Compilation de la librairie, cible : $(CIBLE)
	$(AR) $(ARFLAGS) $(CIBLE) $^

%.o : %.cpp $(H)
	$(CC) $(CFLAGS) $(DEFS) -c $<

clean : cleano cleana cleanbak

cleano :
	$(REMOVE) *.o

cleana :
	$(REMOVE) *.a

cleanbak :
	$(REMOVE) *~
	$(REMOVE) *.bak

edit :
	$(EDITOR) *.cpp *.h Makefile &

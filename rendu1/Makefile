# J.Ropars 364156 and E.Dutruy 355726
# Rendu1

# Definitions de macros

CXX     = g++
CXXFLAGS = -g -Wall -std=c++11

CXXFILES = message.cc particule.cc projet.cc robot.cc shape.cc simulation.cc

OFILES = $(CXXFILES:.cc=.o)

# Instruction conditionnelles
ifeq ($(MAKECMDGOALS), debug)
	CXXFLAGS += -DDEBUG
endif

all: prog
debug: all

# Definition de la premiere regle

prog: $(OFILES)
	$(CXX) $(OFILES) -o projet

# Definitions de cibles particulieres

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ */*.o */*.x */*.cc~ */*.h~ projet test

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
message.o: message.cc message.h
particule.o: particule.cc particule.h shape.h message.h constantes.h
projet.o: projet.cc simulation.h particule.h shape.h robot.h
robot.o: robot.cc robot.h shape.h particule.h message.h constantes.h
shape.o: shape.cc shape.h
simulation.o: simulation.cc simulation.h particule.h shape.h robot.h \
 message.h

# J.Ropars 364156 and E.Dutruy 355726
# Rendu1

# Definitions de macros

CXX       = g++
CXXFLAGS  = -Wall -std=c++17 `pkg-config --cflags gtkmm-4.0`
LIBFLAGS   = `pkg-config --libs gtkmm-4.0`

CXXFILES = message.cc particule.cc projet.cc robot.cc shape.cc \
simulation.cc graphic.cc gui.cc

OFILES = $(CXXFILES:.cc=.o)

# Instruction conditionnelles
ifeq ($(MAKECMDGOALS), debug)
	CXXFLAGS += -DDEBUG
endif

all: prog
debug: all

# Definition de la premiere regle

prog: $(OFILES)
	$(CXX) $(OFILES) -o projet $(LIBFLAGS)

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ */*.o */*.x */*.cc~ */*.h~ projet test

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
message.o: message.cc message.h
particule.o: particule.cc particule.h shape.h message.h constantes.h graphic.h
projet.o: projet.cc simulation.h particule.h shape.h robot.h graphic.h
robot.o: robot.cc robot.h shape.h particule.h message.h constantes.h graphic.h
shape.o: shape.cc shape.h graphic.h
simulation.o: simulation.cc simulation.h particule.h shape.h robot.h \
 message.h graphic.h
gui.o: gui.cc gui.h graphic.h simulation.h robot.h robot.h particule.h message.h \
 shape.h
graphic.o: graphic.cc graphic.h

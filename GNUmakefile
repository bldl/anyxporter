# The primary makefile for this project. A 'Makefile' (if any) is
# generated depending on configuration.

PROG := exportemplapp
SRCDIRS := src console-ui datasrc-qt engine-hw filesys-cxx
DEPFLAGS := $(patsubst %, -I% ,$(SRCDIRS))
CXXFLAGS := -Wall -std=c++0x
LDFLAGS := 
SRCFILES := $(wildcard $(patsubst %, %/*.cpp, $(SRCDIRS)))
OBJFILES := $(patsubst %.cpp, %.o, $(SRCFILES))
GENFILES := 

default : build

-include local.mk

.depend : GNUmakefile $(GENFILES)
	fastdep $(DEPFLAGS) --remakedeptarget=$@ $(SRCFILES) > $@

-include .depend

build : $(PROG)

info:
	@echo $(PROG)
	@echo $(OBJFILES)
	@echo $(SRCFILES)

$(PROG) : $(OBJFILES)
	g++ -o $@ $(OBJFILES) $(LDFLAGS)

%.o : %.cpp
	g++ -c $(CXXFLAGS) $(DEPFLAGS) -o $@ $<

qmake :
	qmake -o qt.mk

qt.mk :
	qmake -o qt.mk

qtbuild : qt.mk
	make -f qt.mk

clean :
	-rm $(PROG) $(OBJFILES) qt.mk

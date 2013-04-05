# The primary makefile for this project. A 'Makefile' (if any) is
# generated depending on configuration.

PROG := exportemplapp
SRCDIRS := src datasrc-dummy engine-hw console-ui
CXXFLAGS := -Wall -std=c++0x
LDFLAGS := 
SRCFILES := $(wildcard $(patsubst %, %/*.cpp, $(SRCDIRS)))
OBJFILES := $(patsubst %.cpp, %.o, $(SRCFILES))

default : build

build : $(PROG)

info:
	@echo $(PROG)
	@echo $(OBJFILES)
	@echo $(SRCFILES)

$(PROG) : $(OBJFILES)
	g++ -o $@ $(OBJFILES) $(LDFLAGS)

%.o : %.cpp
	g++ -c $(CXXFLAGS) $(patsubst %, -I% ,$(SRCDIRS)) -o $@ $<

clean :
	-rm $(PROG) $(OBJFILES)

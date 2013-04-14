# The primary makefile for this project. Plain C++ builds are handled
# directly here, whereas builds for specific toolkits and platforms
# are handled by invoking their respective tools from here.

default : build

# generate for default variant if does not exist at all
src/current_config.mk :
	./configure.sh cxx-dummy

config-default :
	./configure.sh cxx-dummy

include src/current_config.mk

LUA_CFLAGS := -I/usr/include/lua5.1
LUA_LDFLAGS := -llua5.1

PROG := $(APP_BASENAME)
DEPFLAGS := $(patsubst %, -I% ,$(SRCDIRS))
CFLAGS := -Wall $(LUA_CFLAGS)
CXXFLAGS := $(CFLAGS) -std=c++0x
LDFLAGS := $(LUA_LDFLAGS)
SRCFILES := $(wildcard $(patsubst %, %/*.cpp, $(SRCDIRS)))
HDRFILES := $(wildcard $(patsubst %, %/*.hpp, $(SRCDIRS)))
OBJFILES := $(patsubst %.cpp, %.o, $(SRCFILES))
GENFILES := 

-include local.mk

# regenerate for current variant
config : 
	./configure.sh $(VARIANT_NAME)

.depend : GNUmakefile $(GENFILES)
	fastdep $(DEPFLAGS) --remakedeptarget=$@ $(SRCFILES) > $@

-include .depend

ifeq ($(WITH_QMAKE),true)
  ifeq ($(IS_QT_SIMULATOR),true)
    BUILD_RULE := qt-simulator-build
  else
    BUILD_RULE := qt-build
  endif
else
  BUILD_RULE := $(PROG)
endif

build : $(BUILD_RULE)

info:
	@echo "PROGRAM  :" $(PROG)
	@echo "VERSION  :" $(VERSION_STRING)
	@echo "VARIANT  :" $(VARIANT_NAME)
	@echo "SRCDIRS  :" $(SRCDIRS)
	@echo "OBJFILES :" $(OBJFILES)
	@echo "SRCFILES :" $(SRCFILES)

$(PROG) : $(OBJFILES)
	g++ -o $@ $(OBJFILES) $(LDFLAGS)

%.o : %.cpp
	g++ -c $(CXXFLAGS) $(DEPFLAGS) -o $@ $<

define do-qmake
	echo 'SOURCES +=' $(foreach x, $(SRCFILES), $(shell basename $(x))) > src/source_list.pri
	echo 'HEADERS +=' $(foreach x, $(HDRFILES), $(shell basename $(x))) >> src/source_list.pri
	qmake -o qt.mk
endef

qmake :
	$(do-qmake)

qt.mk : $(APP_BASENAME).pro src/current_config.pri
	$(do-qmake)

qt-build : qt.mk
	$(MAKE) -f qt.mk

qt-simulator-build : qt.mk
	@echo "NOTE:" use Qt Creator to build for Qt simulator

clean :
	-rm $(PROG) $(OBJFILES) qt.mk .depend

install :
	sudo aptitude install liblua5.1-0 liblua5.1-0-dev

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

ifeq ($(LUA_LINK_AS),pkg-config)
  LUA_CFLAGS := $(shell pkg-config --cflags lua5.1)
  LUA_LDFLAGS := $(shell pkg-config --libs lua5.1)
  LUA_C_SRCFILES := 
  LUA_CXX_SRCFILES := 
else ifeq ($(LUA_LINK_AS),dynamic-lib)
  LUA_CFLAGS := -I/usr/include/lua5.1
  LUA_LDFLAGS := -llua5.1
  LUA_C_SRCFILES := 
  LUA_CXX_SRCFILES := 
else ifeq ($(LUA_LINK_AS),source-code)
  LUA_CFLAGS := -Ilua-5.2.2/src
  LUA_LDFLAGS :=
  LUA_C_SRCFILES := $(patsubst %, lua-5.2.2/src/%, lapi.c lbaselib.c lcode.c lctype.c ldblib.c ldebug.c ldump.c lfunc.c lgc.c liolib.c llex.c lmem.c lobject.c lopcodes.c lparser.c lstate.c lstring.c ltable.c ltm.c lundump.c lvm.c lzio.c lauxlib.c lbitlib.c lcorolib.c lmathlib.c loadlib.c loslib.c lstrlib.c ltablib.c linit.c)
  LUA_CXX_SRCFILES := $(patsubst %, lua-5.2.2/src/%, ldo.cpp)
else
  $(error unsupported Lua linkage)
endif

PROG := $(APP_BASENAME)
DEPFLAGS := $(patsubst %, -I% ,$(SRCDIRS)) $(LUA_CFLAGS)
CFLAGS := -Wall $(DEPFLAGS)
CXXFLAGS := $(CFLAGS) -std=c++0x
LDFLAGS := $(LUA_LDFLAGS)
C_SRCFILES := $(LUA_C_SRCFILES)
CXX_SRCFILES := $(wildcard $(patsubst %, %/*.cpp, $(SRCDIRS))) $(LUA_CXX_SRCFILES)
SRCFILES := $(C_SRCFILES) $(CXX_SRCFILES)
OBJFILES := $(patsubst %.cpp, %.o, $(CXX_SRCFILES)) $(patsubst %.c, %.o, $(C_SRCFILES))
HDRFILES := $(wildcard $(patsubst %, %/*.hpp, $(SRCDIRS))) $(wildcard $(patsubst %, %/*.h, $(SRCDIRS)))
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
  else ifeq ($(IS_HARMATTAN),true)
    BUILD_RULE := qt-harmattan-build
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
	g++ -c $(CXXFLAGS) -o $@ $<

%.o : %.c
	gcc -c $(CFLAGS) -o $@ $<

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

qt-harmattan-build : qt.mk
	@echo "NOTE:" use Qt Creator to build for MeeGo Harmattan

test : $(PROG)
	@./$(PROG) && cat $(EXPORT_OUTPUT_FILE)

clean :
	-rm $(PROG) $(OBJFILES) qt.mk .depend

install :
	sudo aptitude install liblua5.1-0 liblua5.1-0-dev

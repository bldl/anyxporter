# The primary makefile for this project. Plain C++ builds are handled
# directly here, whereas builds for specific toolkits and platforms
# are handled by invoking their respective tools from here.

default : build

# generate for default variant if does not exist at all
src/current_config.mk :
	./configure.sh cxx-mock

config-default :
	./configure.sh cxx-mock

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
LUA_SRCFILES = $(LUA_C_SRCFILES) $(LUA_CXX_SRCFILES)

PROG := $(APP_BASENAME)
DEPFLAGS := $(patsubst %, -I% ,$(SRCDIRS)) $(LUA_CFLAGS)
CFLAGS := -Wall $(DEPFLAGS)
CXXFLAGS := $(CFLAGS) -std=c++0x
LDFLAGS := $(LUA_LDFLAGS)
CORE_SRCFILES := $(wildcard $(patsubst %, %/*.cpp, $(SRCDIRS)))
CORE_HDRFILES := $(wildcard $(patsubst %, %/*.hpp, $(SRCDIRS))) $(wildcard $(patsubst %, %/*.h, $(SRCDIRS)))
C_SRCFILES := $(LUA_C_SRCFILES)
CXX_SRCFILES :=  $(CORE_SRCFILES) $(LUA_CXX_SRCFILES)
SRCFILES := $(C_SRCFILES) $(CXX_SRCFILES)
OBJFILES := $(patsubst %.cpp, %.o, $(CXX_SRCFILES)) $(patsubst %.c, %.o, $(C_SRCFILES))
GENFILES := 

-include local.mk

# regenerate for current variant
config : 
	./configure.sh $(VARIANT_NAME)

.depend : GNUmakefile $(GENFILES)
	fastdep $(DEPFLAGS) -D__cplusplus --remakedeptarget=$@ $(SRCFILES) > $@

-include .depend

ifeq ($(WITH_QMAKE),true)
  ifeq ($(IS_QT_SIMULATOR),true)
    BUILD_RULE := qt-simulator-build
  else ifeq ($(IS_HARMATTAN),true)
    BUILD_RULE := qt-harmattan-build
  else
    BUILD_RULE := qt-build
  endif
else ifeq ($(WITH_SBSV1),true)
  BUILD_RULE := sbsv1-build
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
	echo 'SOURCES +=' $(foreach x, $(CORE_SRCFILES), $(shell basename $(x))) > src/source_list.pri
	echo 'HEADERS +=' $(foreach x, $(CORE_HDRFILES), $(shell basename $(x))) >> src/source_list.pri
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

BUILD_DIR := build/$(VARIANT_NAME)

do-build-dir :
	mkdir -p $(BUILD_DIR)

WITH_GNUPOC := in-gnupoc-env --gcc $(GCC_NAME) $(KIT_NAME)

RBFILTER := ruby -r src/current_config.rb -e 'require "erb"; puts(ERB.new(ARGF.read()).result(binding()))'

SRCLIST_RB := src/source_list.rb
RBFILTER_MMP := ruby -r src/current_config.rb -r $(SRCLIST_RB) -e 'require "erb"; puts(ERB.new(ARGF.read()).result(binding()))'

bld-inf : do-build-dir
	cat src/bld.inf.in | $(RBFILTER) > $(BUILD_DIR)/bld.inf

mmp-info :
	echo '$$SRCFILES = %w{' $(SRCFILES) '}' > $(SRCLIST_RB)

mmp-file : do-build-dir mmp-info
	cat src/module.mmp.in | $(RBFILTER_MMP) > $(BUILD_DIR)/$(APP_BASENAME).mmp

do-bldmake : bld-inf mmp-file
	cd $(BUILD_DIR) && $(WITH_GNUPOC) bldmake bldfiles

do-abld :
	cd $(BUILD_DIR) && $(WITH_GNUPOC) abld build -v $(ABLD_ARCHITECTURE) $(ABLD_VARIANT)

abld-reallyclean :
	cd $(BUILD_DIR) && $(WITH_GNUPOC) abld reallyclean

SIS_BASEFILE := $(APP_BASENAME)-$(VERSION_STRING)-$(VARIANT_NAME).sis
SIS_FILE := $(BUILD_DIR)/$(SIS_BASEFILE)
SISX_FILE := $(SIS_FILE)x
INSTALL_FILE := $(if $(IS_ELF),$(SISX_FILE),$(SIS_FILE))

pkg-file : do-build-dir
	cat src/module.pkg.in | $(RBFILTER) > $(BUILD_DIR)/$(APP_BASENAME).pkg

do-makesis : pkg-file
	cd $(BUILD_DIR) && $(WITH_GNUPOC) makesis -d$(shell $(WITH_GNUPOC) printenv EPOCROOT) $(APP_BASENAME).pkg $(SIS_BASEFILE)

do-sign-sis :
	$(WITH_GNUPOC) signsis -s $(SIS_FILE) $(SISX_FILE) certs/$(CERT_NAME).cer certs/$(CERT_NAME).key my-secret

do-build-sis : do-makesis $(and $(SIGNED), do-sign-sis)

sbsv1-build : do-bldmake do-abld do-build-sis

test : build
	@./$(PROG) && cat $(EXPORT_OUTPUT_FILE)

test-post : build
	@DO_HTTP_POST=true ./$(PROG) && cat $(EXPORT_OUTPUT_FILE)

clean :
	-rm $(PROG) $(OBJFILES) *.o moc_*.cpp qt.mk .depend Makefile

sys-install :
	sudo aptitude install liblua5.1-0 liblua5.1-0-dev

# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_USR := $(subst \,/,$(WIND_USR))

all : pre_build main_all post_build

_clean ::
	@echo "make: removing targets and objects of `pwd`"

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

MAKEFILE := Makefile

FLEXIBLE_BUILD := 1

BUILD_SPEC = PPC603gnu
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
PRJ_ROOT_DIR := C:/WindRiver/workspace/Team2502Code
WS_ROOT_DIR := C:/WindRiver/workspace



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0


#BuildSpec specific Build Macros
VX_CPU_FAMILY = ppc
CPU = PPC603
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp -mlongcall
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/WPILib -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = $(WIND_BASE)/target/lib/WPILib.a 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
DEBUGFLAGS_C++-Compiler = -g
DEBUGFLAGS_Linker = -g
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
DEBUGFLAGS_Linker = -O2 -fstrength-reduce -fno-builtin
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif


#Project Targets
PROJECT_TARGETS = Team2502Code/$(MODE_DIR)/Team2502Code.out \
	 Team2502Code_partialImage/$(MODE_DIR)/Team2502Code_partialImage.o


#Rules

# Team2502Code
ifeq ($(DEBUG_MODE),1)
Team2502Code/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
Team2502Code/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
Team2502Code/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
Team2502Code/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
Team2502Code/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
Team2502Code/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
Team2502Code/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
Team2502Code/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
Team2502Code/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -O2 -fstrength-reduce -fno-builtin
Team2502Code/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
Team2502Code/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
Team2502Code/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
Team2502Code/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/WPILib -I$(WIND_BASE)/target/h/wrn/coreip 
Team2502Code/$(MODE_DIR)/% : IDE_LIBRARIES = $(WIND_BASE)/target/lib/WPILib.a 
Team2502Code/$(MODE_DIR)/% : PROJECT_TYPE = DKM
Team2502Code/$(MODE_DIR)/% : DEFINES = 
Team2502Code/$(MODE_DIR)/% : EXPAND_DBG = 0
Team2502Code/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
Team2502Code/$(MODE_DIR)/% : CPU = PPC603
Team2502Code/$(MODE_DIR)/% : TOOL_FAMILY = gnu
Team2502Code/$(MODE_DIR)/% : TOOL = gnu
Team2502Code/$(MODE_DIR)/% : TOOL_PATH = 
Team2502Code/$(MODE_DIR)/% : CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp -mlongcall
Team2502Code/$(MODE_DIR)/% : LIBPATH = 
Team2502Code/$(MODE_DIR)/% : LIBS = 
Team2502Code/$(MODE_DIR)/% : OBJ_DIR := Team2502Code/$(MODE_DIR)

OBJECTS_Team2502Code = Team2502Code_partialImage/$(MODE_DIR)/Team2502Code_partialImage.o

Team2502Code/$(MODE_DIR)/Team2502Code.out : $(OBJECTS_Team2502Code)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";nmppc $(OBJECTS_Team2502Code) $(IDE_LIBRARIES) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c ppc > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -fdollars-in-identifiers -Wall $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES)  -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccppc -r -nostdlib -Wl,-X -T $(WIND_BASE)/target/h/tool/gnu/ldscripts/link.OUT -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_Team2502Code) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS)  $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

Team2502Code/$(MODE_DIR)/Team2502Code_compile_file : $(FILE) ;

_clean :: Team2502Code/$(MODE_DIR)/Team2502Code_clean

Team2502Code/$(MODE_DIR)/Team2502Code_clean : 
	$(TRACE_FLAG)if [ -d "Team2502Code" ]; then cd "Team2502Code"; rm -rf $(MODE_DIR); fi


# Team2502Code_partialImage
ifeq ($(DEBUG_MODE),1)
Team2502Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
Team2502Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
Team2502Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
Team2502Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
Team2502Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
Team2502Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
Team2502Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
Team2502Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
Team2502Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -O2 -fstrength-reduce -fno-builtin
Team2502Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
Team2502Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
Team2502Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
Team2502Code_partialImage/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/WPILib -I$(WIND_BASE)/target/h/wrn/coreip 
Team2502Code_partialImage/$(MODE_DIR)/% : IDE_LIBRARIES = $(WIND_BASE)/target/lib/WPILib.a 
Team2502Code_partialImage/$(MODE_DIR)/% : PROJECT_TYPE = DKM
Team2502Code_partialImage/$(MODE_DIR)/% : DEFINES = 
Team2502Code_partialImage/$(MODE_DIR)/% : EXPAND_DBG = 0
Team2502Code_partialImage/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
Team2502Code_partialImage/$(MODE_DIR)/% : CPU = PPC603
Team2502Code_partialImage/$(MODE_DIR)/% : TOOL_FAMILY = gnu
Team2502Code_partialImage/$(MODE_DIR)/% : TOOL = gnu
Team2502Code_partialImage/$(MODE_DIR)/% : TOOL_PATH = 
Team2502Code_partialImage/$(MODE_DIR)/% : CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp -mlongcall
Team2502Code_partialImage/$(MODE_DIR)/% : LIBPATH = 
Team2502Code_partialImage/$(MODE_DIR)/% : LIBS = 
Team2502Code_partialImage/$(MODE_DIR)/% : OBJ_DIR := Team2502Code_partialImage/$(MODE_DIR)

Team2502Code_partialImage/$(MODE_DIR)/Objects/Team2502Code/Onyx.o : C:/WindRiver/workspace/Team2502Code/Onyx.cpp
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Team2502Code_partialImage/$(MODE_DIR)/Objects/Team2502Code/Output.o : C:/WindRiver/workspace/Team2502Code/Output.cpp
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Team2502Code_partialImage/$(MODE_DIR)/Objects/Team2502Code/Pneumatics.o : C:/WindRiver/workspace/Team2502Code/Pneumatics.cpp
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Team2502Code_partialImage/$(MODE_DIR)/Objects/Team2502Code/Vision.o : C:/WindRiver/workspace/Team2502Code/Vision.cpp
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


OBJECTS_Team2502Code_partialImage = Team2502Code_partialImage/$(MODE_DIR)/Objects/Team2502Code/Onyx.o \
	 Team2502Code_partialImage/$(MODE_DIR)/Objects/Team2502Code/Output.o \
	 Team2502Code_partialImage/$(MODE_DIR)/Objects/Team2502Code/Pneumatics.o \
	 Team2502Code_partialImage/$(MODE_DIR)/Objects/Team2502Code/Vision.o

Team2502Code_partialImage/$(MODE_DIR)/Team2502Code_partialImage.o : $(OBJECTS_Team2502Code_partialImage)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc -r -nostdlib -Wl,-X  -o "$@" $(OBJECTS_Team2502Code_partialImage) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS)  && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

Team2502Code_partialImage/$(MODE_DIR)/Team2502Code_partialImage_compile_file : $(FILE) ;

_clean :: Team2502Code_partialImage/$(MODE_DIR)/Team2502Code_partialImage_clean

Team2502Code_partialImage/$(MODE_DIR)/Team2502Code_partialImage_clean : 
	$(TRACE_FLAG)if [ -d "Team2502Code_partialImage" ]; then cd "Team2502Code_partialImage"; rm -rf $(MODE_DIR); fi

DEP_FILES := Team2502Code_partialImage/$(MODE_DIR)/Objects/Team2502Code/Onyx.d Team2502Code_partialImage/$(MODE_DIR)/Objects/Team2502Code/Output.d Team2502Code_partialImage/$(MODE_DIR)/Objects/Team2502Code/Pneumatics.d \
	 Team2502Code_partialImage/$(MODE_DIR)/Objects/Team2502Code/Vision.d
-include $(DEP_FILES)



-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

main_all : external_build $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""

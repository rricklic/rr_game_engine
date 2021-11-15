STATIC_LIB = librr.a
SHARED_LIB = librr.so

CC = gcc
# NOTE: -g3 debugging info with macros
CFLAGS = -g3 -Werror-implicit-function-declaration -Wall -Wextra -Wno-unused-function -std=c99 # TODO: c89
INCLUDE = -I./src `pkg-config --cflags glib-2.0` -I/usr/include/SDL2 -D_REENTRANT 

# TODO: put back -lGLEW; remove linux-gnu
LDLIBS = -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_image -lSDL2_ttf -lm -lGLU -lGL -lglib-2.0

# Build/debugging defines
#   RR_ENGINE_SDL, RR_ENGINE_SDL_64, RR_ENGINE_GL, RR_ENGINE_GL_64, RR_ENGINE_64, RR_ENGINE_DOUBLE
#   RR_DEBUG
DEFINE = -DRR_ENGINE_SDL
#-DRR_DEBUG

# Gather *.c sources in src/ and nested directories
SOURCES = $(wildcard src/**/*.c src/*.c)

# Replace all src/%.c in $SOURCES to build/%.o
OBJECTS = $(patsubst src/%,build/%,$(SOURCES:.c=.o))

# Replace all %.o in $OBJECTS to %.d
DEPENDS = $(patsubst %.o,%.d,$(OBJECTS))

# Pull in dependency info from existing *.d files
-include $(DEPENDS)

# Compiler generated dependency files
DEPFLAGS = -MMD -MF $(@:.o=.d)

#######################################
# General GNU Makefile rule structure
#
# target ... : (prerequisities) ...
#	...
#	command
#######################################

#######################################
# Automatic variables in rules
#
# $@ - target name
# $< - first prerequisites
# $^ - all prerequisites
########################################

# TODO: PRINT VARIABLES
# $(info TARGETS is $(TARGETS)) $(info SOURCES is $(SOURCES)) $(info OBJECTS is $(OBJECTS)) $(info DEPFLAGS is $(DEPFLAGS))

# Default target
.PHONY: all
all: $(STATIC_LIB)

# Link, create static library
$(STATIC_LIB): $(OBJECTS)
	$(MAKE) mkdirs
	ar rcs bin/$@ $^

# TODO:
# Link, create shared (dynamic) library
# $(SHARED_LIB): $(OBJECTS)
#	$(MAKE) mkdirs
#	$(CC) -shared $^ -o bin/$@

# Compile
build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) $(DEFINE) -c $< -o $@ $(DEPFLAGS)

mkdirs:
	@mkdir -p build
	@mkdir -p bin

clean:
	rm -rf build bin

# Potentially dangerous functions
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tol|_)|stpn?cpy|a?sn?printf|byte_)'

check:
	@echo Files with potentially dangerous functions
	@egrep $(BADFUNCS) $(SOURCES) || true

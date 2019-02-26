OSFLAG :=
ifeq ($(OS),Windows_NT)
	OSFLAG += -D WIN32
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		OSFLAG += -D AMD64
	endif
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		OSFLAG += -D IA32
	endif
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG += -D LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		OSFLAG += -D OSX
	endif
		UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		OSFLAG += -D AMD64
	endif
		ifneq ($(filter %86,$(UNAME_P)),)
	OSFLAG += -D IA32
		endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		OSFLAG += -D ARM
	endif
endif

# Chosen compiler
CC := gcc
# Compilation flags
CFLAGS := -Iinc/ -Wall -Wextra -pedantic
# Source folder
SRC := src
# GLUT source files
GLUTC := $(wildcard $(SRC)/*_glut.c)
# Libraries to include
ifneq ($(OSFLAG),Linux )
    GLUT_LIBS := -lglut32 -lglu32 -lopengl32 -lm
endif
ifeq ($(OSFLAG),Linux )
    GLUT_LIBS := -lGL -lGLU -lglut -lm
endif

# Makfile targets
pong_glut:
	$(CC) $(GLUTC) -o $@ $(CFLAGS) $(GLUT_LIBS)

.PHONY: clean

clean:
	rm -f *.o pong_glut
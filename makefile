# Chosen compiler
CC := gcc
# Compilation flags
CFLAGS := -Iinc/ -Wall -Wextra -pedantic
# Source folder
SRC := src
# GLUT source files
GLUTC := $(wildcard $(SRC)/*_glut.c)
# Libraries to include
GLUT_LIBS := -lGL -lGLU -lglut -lm

pong_glut:
	$(CC) $(GLUTC) -o $@ $(CFLAGS) $(GLUT_LIBS)

.PHONY: clean

clean:
	rm -f *.o pong_glut
# Chosen compiler
CC := gcc

# Compilation flags
CFLAGS := -Iinc/glut -Wall -Wextra -pedantic

# Source folder
SRC_GLUT := src/glut

# GLUT source files
GLUTC := $(wildcard $(SRC_GLUT)/*_glut.c)

# Libraries to include for windows
# GLUT_LIBS := -lglut32 -lglu32 -lopengl32 -lm
GLUT_LIBS := -lGL -lGLU -lglut -lm

# Makfile targets
pong_glut:
	$(CC) $(GLUTC) -o $@ $(CFLAGS) $(GLUT_LIBS)

.PHONY: clean

clean:
	rm -f *.o pong_glut

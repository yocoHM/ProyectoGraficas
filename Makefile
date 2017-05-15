CC = gcc
CXX = g++
LDFLAGS = -lIL -lglm -ljpeg -lpng $(LIBGL)
CPPFLAGS = -Wno-deprecated-declarations
TARGET = final.out
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

ifeq ($(shell uname -s), Darwin)
	LIBGL = -framework OpenGL -framework GLUT -framework CoreFoundation
else
	LIBGL = -lGL -lGLU -lglut
endif

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(GLMA) $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f *.o *.out $(TARGET)


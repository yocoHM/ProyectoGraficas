CC = g++
CXX = g++
LDFLAGS =  -lIL -lglm -ljpeg -lpng -lSOIL -lm $(LIBGL)
CPPFLAGS = -std=c++0x -Wno-deprecated-declarations
TARGET = final
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)

ifeq ($(shell uname -s), Darwin)
	LIBGL = -framework OpenGL -framework GLUT -framework CoreFoundation
else
	LIBGL = -lGL -lGLU -lglut
endif

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f *.o *.out $(TARGET)

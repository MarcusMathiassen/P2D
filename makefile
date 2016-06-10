
CC := g++-5

CFLAGS := -std=c++14 -lpthread -lglew -lglfw3 -fopenmp -framework OpenGL -Ofast

COMPILE_COMMAND := $(CC) $(CFLAGS)

OUTPUT := P2D_v0.5

SRC := main.cpp Object.cpp Quadtree.cpp Process.cpp Rect.cpp Render.cpp Inputs.cpp Circle.cpp Color.cpp Config.cpp Vec2.cpp Utility.cpp DynamicGrid.cpp

all:
	$(COMPILE_COMMAND) -o $(OUTPUT) $(SRC)

clean:
	rm -f *.o $(OUTPUT).*
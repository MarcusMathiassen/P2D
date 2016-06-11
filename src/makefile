
CC := g++-5

CFLAGS := -std=c++14 -lpthread -lglew -lglfw3 -fopenmp -framework OpenGL -Ofast

COMPILE_COMMAND := $(CC) $(CFLAGS)

OUTPUT := P2D_v0.6

SRC := main.cpp Config.cpp Process.cpp Render.cpp ./DynamicGrid/DynamicGrid.cpp ./DynamicGrid/Node.cpp ./Objects/Object.cpp ./Objects/Shapes/Circle.cpp ./Objects/Shapes/Rect.cpp ./Quadtree/Quadtree.cpp ./Utility/Color.cpp ./Utility/Inputs.cpp ./Utility/Utility.cpp ./Utility/Vec2.cpp ./Utility/getTime64.cpp

all:
	$(COMPILE_COMMAND) -o $(OUTPUT) $(SRC)

clean:
	rm -f *.o $(OUTPUT).*
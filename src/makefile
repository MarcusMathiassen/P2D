
CC := g++-5

CFLAGS := -std=c++14 -lpthread -lglew -lglfw3 -fopenmp -framework OpenGL -Ofast -ffast-math -Wall -Wold-style-cast
COMPILE_COMMAND := $(CC)

OUTPUT := P2D_v06

SRC := main.cpp ./Config/Config.cpp ./Process/Process.cpp ./Render/Render.cpp ./SpatialHash/SpatialHash.cpp ./SpatialHash/Node/Node.cpp ./Objects/Object.cpp ./Objects/Circle/Circle.cpp ./Objects/Rectangle/Rect.cpp ./Quadtree/Quadtree.cpp ./Utility/Color.cpp ./Utility/Inputs.cpp ./Utility/Utility.cpp ./Utility/Vec2.cpp ./Utility/getTime64.cpp
all:
	$(COMPILE_COMMAND) $(SRC) $(CFLAGS) -o $(OUTPUT)

clean:
	rm -f *.o $(OUTPUT)*
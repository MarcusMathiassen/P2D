
CC := g++-6

CFLAGS := -std=c++14 -lpthread -lglew -lglfw3 -framework OpenGL -Ofast -ffast-math -Wall
COMPILE_COMMAND := $(CC)

OUTPUT := /usr/local/bin/P2D

SRC := ./src/main.cpp ./src/Config/Config.cpp ./src/Process/Process.cpp ./src/Render/Render.cpp ./src/FixedGrid/FixedGrid.cpp ./src/FixedGrid/Node/Node.cpp ./src/Objects/Circle/Circle.cpp ./src/Objects/Rectangle/Rect.cpp ./src/Quadtree/Quadtree.cpp ./src/Utility/Color.cpp ./src/Utility/Inputs.cpp ./src/Utility/Utility.cpp ./src/Utility/Vec2.cpp ./src/Utility/getTime64.cpp
all:
	@$(COMPILE_COMMAND) $(SRC) $(CFLAGS) -o $(OUTPUT)

clean:
	rm -f *.o $(OUTPUT)*
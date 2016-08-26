
CC := g++

CFLAGS := -std=c++14 -lpthread -lglew -lglfw3 -framework OpenGL -Ofast -ffast-math
COMPILE_COMMAND := $(CC)

OUTPUT := P2Dv06

SRC := main.cpp ./Config/Config.cpp ./Process/Process.cpp ./Render/Render.cpp ./FixedGrid/FixedGrid.cpp ./FixedGrid/Node/Node.cpp ./Objects/Circle/Circle.cpp ./Objects/Rectangle/Rect.cpp ./Quadtree/Quadtree.cpp ./Utility/Color.cpp ./Utility/Inputs.cpp ./Utility/Utility.cpp ./Utility/Vec2.cpp ./Utility/getTime64.cpp
all:
	$(COMPILE_COMMAND) $(SRC) $(CFLAGS) -o $(OUTPUT)

clean:
	rm -f *.o $(OUTPUT)*
#include "Inputs.h"
#include "Object.h"
#include "Circle.h"
#include "Config.h"
#include "Color.h"

#include <iostream>

double mousePosX, mousePosY;

void Inputs(GLFWwindow* window) {

	/* 
	
	While 4 is pressed. Spawn balls at mouse position.

	G : Gravity on/off
	D : Direction on/off

	F : Show FPS on/off
	L : Lock FPS on/offx
	
	8 : Decrease threads by 1
	9 : Increase threads by 1
	0 : Turn on pThreads

	*/

	// Update cursor position
	glfwGetCursorPos(window, &mousePosX, &mousePosY);

	// Spawn balls
	if(glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		object_v.push_back(std::unique_ptr<Object>
			(new Circle(Vec2(mousePosX,WINDOW_HEIGHT-mousePosY),1,10)));
		std::cout << object_v.size() << std::endl;
	}
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {

	/* Color */
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		uniCol++;
		std::cout << "Cycled color" << std::endl;
	}

	/* Delete all */
	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		object_v.clear();
		std::cout << "Deleted all objects" << std::endl;
	}

	/* Gravity */
	if (key == GLFW_KEY_G && action == GLFW_PRESS) {
		if (gravity == false) {
			gravity = true;
			std::cout << "Gravity ON" << std::endl;
		} else  {
			gravity = false;
			std::cout << "Gravity OFF" << std::endl;
		}
	}

	/* gravForce */
	if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		if (gravForce == false) {
			std::cout << "Gravitasion force ON" << std::endl;
			gravForce = true;
		} else {
			gravForce = false;
			std::cout << "Gravitasion force OFF" << std::endl;
		}
	}

	/* gravForce COLORS  */
	if (key == GLFW_KEY_Y && action == GLFW_PRESS) {
		if (gravForceCol == false) {
			std::cout << "Gravitasion force COLORS ON" << std::endl;
			gravForceCol = true;
		} else {
			gravForceCol = false;
			std::cout << "Gravitasion force COLORS OFF" << std::endl;
		}
	}

	/* borderCol */
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		if (borderCol == false) {
			borderCol = true;
			std::cout << "Border collision ON" << std::endl;
		} else {
			borderCol = false;
			std::cout << "Border collision OFF" << std::endl;
		}
	}

	/* ballCol */
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		if (ballCol == false) {
			ballCol = true;
			std::cout << "Ball collision ON" << std::endl;
		} else {
			ballCol = false;
			std::cout << "Ball collision OFF" << std::endl;
		}
	}

	/* useQuadtree */
	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		if (useQuadtree == false) {
			useQuadtree = true;
			std::cout << "Quadtrees ON" << std::endl;
		} else {
			useQuadtree = false;
			std::cout << "Quadtrees OFF" << std::endl;
		}
	}

	/* Slowmotion */
	if (key == GLFW_KEY_O && action == GLFW_PRESS) {
		if (slowmotion == false) {
			slowmotion = true;
			std::cout << "Slowmotion ON" << std::endl;
		} else {
			slowmotion = false;
			std::cout << "Slowmotion OFF" << std::endl;
		}
	}

	/* Show FPS */
	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		if (showFPS == false) {
			showFPS = true;
			std::cout << "Show FPS ON" << std::endl;
		} else {
			showFPS = false;
			std::cout << "Show FPS OFF" << std::endl;
		}
	}

	/* Unlock FPS */
	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		if (unlockFPS == false) {
			unlockFPS = true;
			std::cout << "FPS LOCK OFF" << std::endl;
		} else {
			unlockFPS = false;
			std::cout << "FPS LOCK ON" << std::endl;
		}
	}

	/* Direction */
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		if (direction == false) {
			direction = true;
			std::cout << "Direction ON" << std::endl;
		} else {
			direction = false;
			std::cout << "Direction OFF" << std::endl;
		}
	}

	/* Quadtrees */
	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		if (drawQuadtrees == false) {
			drawQuadtrees = true;
			std::cout << "drawQuadtrees ON" << std::endl;
		} else {
			drawQuadtrees = false;
			std::cout << "drawQuadtrees OFF" << std::endl;
		}
	}

	/* pThread */
	if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
		if (use_pThread == false) {
			use_pThread = true;
			std::cout << "using pThreads" << std::endl;
		} else {
			use_pThread = false;
			std::cout << "using OpenMP" << std::endl;
		}
	}

	/* Threads */
	if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
		numThreads++;
		std::cout << "Number of threads: " << numThreads << std::endl;
	}

	if (key == GLFW_KEY_8 && action == GLFW_PRESS && numThreads > 0) {
		numThreads--;
		std::cout << "Number of threads: " << numThreads << std::endl;
	}

}

void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {
	mousePosX = xpos;
	mousePosY = ypos;
	//std::cout << "POS: " << mousePosX << ", " << mousePosY << std::endl;
}

void cursorEnterCallback(GLFWwindow *window, int entered) {
	if (entered) {
		//std::cout << "Entered window" << std::endl;
	}
	else {
		//std::cout << "Leaves window" << std::endl;
	}
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		object_v.push_back(std::unique_ptr<Object>
			(new Circle(Vec2(mousePosX,WINDOW_HEIGHT-mousePosY),30,30)));
		// Left mouse button pressed.
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		// Left mouse button released.
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		//std::cout << "Right button pressed" << std::endl;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		//std::cout << "Right button released" << std::endl;
	}
}

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {

}

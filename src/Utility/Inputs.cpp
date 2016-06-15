#include "Inputs.h"

void Inputs(GLFWwindow* window) {

	// Update cursor position
	glfwGetCursorPos(window, &xpos, &ypos);
	if (windowResized) { xpos*=2, ypos*=2;}

	// Make sure the mousepointer is inside the window
	if (isInWindow)
	{
		// Spawn balls
		if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
			object_vec.push_back(uptr<Object>
				(new Circle(Vec2(xpos,screen_height-ypos),1,6)));
			object_vec.push_back(uptr<Object>
				(new Circle(Vec2(xpos,screen_height-ypos),1,6)));
			object_vec.push_back(uptr<Object>
				(new Circle(Vec2(xpos,screen_height-ypos),1,6)));
			object_vec.push_back(uptr<Object>
				(new Circle(Vec2(xpos,screen_height-ypos),1,6)));
			object_vec.push_back(uptr<Object>
				(new Circle(Vec2(xpos,screen_height-ypos),1,6)));
			object_vec.push_back(uptr<Object>
				(new Circle(Vec2(xpos,screen_height-ypos),1,6)));
			object_vec.push_back(uptr<Object>
				(new Circle(Vec2(xpos,screen_height-ypos),1,6)));
			object_vec.push_back(uptr<Object>
				(new Circle(Vec2(xpos,screen_height-ypos),1,6)));
			object_vec.push_back(uptr<Object>
				(new Circle(Vec2(xpos,screen_height-ypos),1,6)));
			object_vec.push_back(uptr<Object>
				(new Circle(Vec2(xpos,screen_height-ypos),1,6)));
			object_vec.push_back(uptr<Object>
				(new Circle(Vec2(xpos,screen_height-ypos),1,6)));
			//std::cout << object_vec.size() << std::endl;
		}
		// Spawn balls
		if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
			object_vec.push_back(uptr<Object>
				(new Circle(Vec2(xpos,screen_height-ypos),3,10)));
			//std::cout << object_vec.size() << std::endl;
		}
		// Spawn balls
		if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
			object_vec.push_back(uptr<Object>
				(new Circle(Vec2(xpos,screen_height-ypos),6,15)));
			//std::cout << object_vec.size() << std::endl;
		}
		// Spawn balls
		if(glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
			object_vec.push_back(uptr<Object>
				(new Circle(Vec2(xpos,screen_height-ypos),10,20)));
			//std::cout << object_vec.size() << std::endl;
		}
		// Spawn balls
		if(glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
			object_vec.push_back(uptr<Object>
				(new Circle(Vec2(xpos,screen_height-ypos),20,25)));
			//std::cout << object_vec.size() << std::endl;
		}
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
		object_vec.clear();
		object_vec.shrink_to_fit();
		spatialHash.init();
		quadtree.init();
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

	/* borderCol */
	if (key == GLFW_KEY_N && action == GLFW_PRESS) {
		if (borderCol == false) {
			borderCol = true;
			std::cout << "Border collision ON" << std::endl;
		} else {
			borderCol = false;
			std::cout << "Border collision OFF" << std::endl;
		}
	}

	/* ballCol */
	if (key == GLFW_KEY_M && action == GLFW_PRESS) {
		if (ballCol == false) {
			ballCol = true;
			std::cout << "Ball collision ON" << std::endl;
		} else {
			ballCol = false;
			std::cout << "Ball collision OFF" << std::endl;
		}
	}

	/* useQuadtree */
	if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		if (use_Quadtree == false) {
			use_Quadtree = true;
			use_DynamicGrid = false;
			std::cout << "Quadtree ON" << std::endl;
		} else {
			use_Quadtree = false;
			std::cout << "Quadtree OFF" << std::endl;
		}
	}

	/* showQuadtrees */
	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		if (show_Quadtree == false) {
			show_Quadtree = true;
			std::cout << "showQuadtree ON" << std::endl;
		} else {
			show_Quadtree = false;
			std::cout << "showQuadtree OFF" << std::endl;
		}
	}

	/* use_DynamicGrid */
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		if (use_DynamicGrid == false) {
			use_DynamicGrid = true;
			use_Quadtree = false;
			std::cout << "DynamicGrids ON" << std::endl;
		} else {
			use_DynamicGrid = false;
			std::cout << "DynamicGrids OFF" << std::endl;
		}
	}

	/* show_DynamicGrid */
	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		if (show_DynamicGrid == false) {
			show_DynamicGrid = true;
			std::cout << "show_DynamicGrid ON" << std::endl;
		} else {
			show_DynamicGrid = false;
			std::cout << "show_DynamicGrid OFF" << std::endl;
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
		if (show_FPS == false) {
			show_FPS = true;
			std::cout << "Show FPS ON" << std::endl;
		} else {
			show_FPS = false;
			std::cout << "Show FPS OFF" << std::endl;
		}
	}

	/* lock FPS */
	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		if (lock_FPS == false) {
			lock_FPS = true;
			std::cout << "FPS LOCK ON" << std::endl;
		} else {
			lock_FPS = false;
			std::cout << "FPS LOCK OFF" << std::endl;
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


	/* uniGrid */
	if (key == GLFW_KEY_6 && action == GLFW_PRESS && griduni > 0) {
		griduni--;
		assignGrid();
		spatialHash.init();
		std::cout << "Dynamic Grids: " << uniGrid << std::endl;
	}

	if (key == GLFW_KEY_7 && action == GLFW_PRESS && griduni < 4) {
		griduni++;
		assignGrid();
		spatialHash.init();
		std::cout << "Dynamic Grids: " << uniGrid << std::endl;
	}

	/* numThreads */
	if (key == GLFW_KEY_8 && action == GLFW_PRESS && numThreads > 0) {
		numThreads--;
		std::cout << "Number of threads: " << numThreads << std::endl;
	}

	if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
		numThreads++;
		std::cout << "Number of threads: " << numThreads << std::endl;
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

}

void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {
}

void cursorEnterCallback(GLFWwindow *window, int entered) {
	if (entered) {
		//std::cout << "Entered window" << std::endl;
		isInWindow = true;
	}
	else {
		//std::cout << "Leaves window" << std::endl;
		isInWindow = false;
	}
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && isInWindow) {
		object_vec.push_back(uptr<Object>
			(new Circle(Vec2(xpos,screen_height-ypos),30,30)));
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
	static_cast<Circle&>(*object_vec[0]).addVel(xoffset*15,-yoffset*15);
}

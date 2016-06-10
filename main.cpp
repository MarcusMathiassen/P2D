//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

// --------------------------------- INCLUDES ---------------------------------

#include <iostream>								// cout
#include <GL/glew.h>							// GLEW setup.
#include <GLFW/glfw3.h>							// GLFW setup.

#include "Config.h"								// Global settings
#include "Color.h"								// Color
#include "Inputs.h"								// User input
#include "Process.h"							// Updates all objects 
#include "Render.h"								// Renders all objects
#include "DynamicGrid.h"						// Grid for collision
#include "Object.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   /* Tranform into pixel coordinates */
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1);

	screen_width = width;
	screen_height = height;

	windowResized = true;
	dynamicGrid.init();
}

int main()
{
	GLFWwindow* window;

	if (!glfwInit()) { std::cout << "GLFW INIT FAILED!\n"; }

	#ifdef MULTISAMPLING 
		glfwWindowHint(GLFW_SAMPLES, xMSAA); 
	#endif

	window = glfwCreateWindow(screen_width, screen_height, WINDOW_NAME, NULL, NULL);

	if (!glewInit()) { std::cout << "GLEW INIT FAILED!\n"; }

	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorEnterCallback(window, cursorEnterCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetKeyCallback(window, keyCallback);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	/* Enable multisampling */
	#ifdef MULTISAMPLING 
		glEnable(GL_MULTISAMPLE);
	#endif

	/* Make the window´s context current */
	glfwMakeContextCurrent(window);

    /* FOR FPS COUNTER */
	float lastTime = glfwGetTime();
   	int nbFrames = 0;

   	/* Tranform into pixel coordinates */
   	glViewport(0, 0, screen_width*2, screen_height*2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, screen_width, 0, screen_height, -1, 1);

	glClearColor(BCKGRND.r,BCKGRND.g,BCKGRND.b,1);

	dynamicGrid.init();

    while (!glfwWindowShouldClose(window)) {

		float currentTime = glfwGetTime();
		nbFrames++;
		if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
		 	if (showFPS) {
		    	printf("\n%f ms/frame\n", 1000/float(nbFrames));
		    	std::cout << "Nodes: " << numNodes << std::endl;
				std::cout << "Circles: " << object_vec.size() << std::endl;
		    }
		    nbFrames = 0;
		    lastTime++;  
		}

    	/* Keyboard, Mouse, Joystick */
		Inputs(window);

		/* Background color */
		glClear(GL_COLOR_BUFFER_BIT);

		update();		// Updates all objects
		draw();			// Draws all objects to screen

		/* Swap interval */
		if (unlockFPS) {
			glfwSwapInterval(0);
		} else glfwSwapInterval(1);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* ESC to quit */
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			break;
		}

		//std::cout << "Comparisons: " << comparisons << std::endl;
		comparisons = 0;
	}

	/* Terminate window */
	glfwTerminate();

	return 0;
}

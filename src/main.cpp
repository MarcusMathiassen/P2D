//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

// --------------------------------- INCLUDES ---------------------------------

#include <iostream>								// cout
#include <GL/glew.h>							// GLEW setup.
#include <GLFW/glfw3.h>							// GLFW setup.

#include "Config.h"								// Global settings
#include "Process.h"							// Updates all objects 
#include "Render.h"								// Renders all objects
#include "./Utility/Color.h"					// Color
#include "./Utility/Inputs.h"					// User input
#include "./Objects/Object.h"					// Object class
#include "./DynamicGrid/DynamicGrid.h"			// dynamicGrid

// ----------------------------------------------------------------------------

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// ---------------------------------------------------------------------
	// Is called whenever the window is resized.
	// ---------------------------------------------------------------------

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

// --------------------------------- LOOP -------------------------------------

    while (!glfwWindowShouldClose(window)) {

		float currentTime = glfwGetTime();
		nbFrames++;

		if ( currentTime - lastTime >= 1.0 )
		{
		 	if (show_FPS) {
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
		if (lock_FPS) {
			glfwSwapInterval(1);
		} else glfwSwapInterval(0);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* ESC to quit */
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			break;
		}
		
		comparisons = 0;
	}

// ----------------------------------------------------------------------------


	/* Terminate window */
	glfwTerminate();

	return 0;
}

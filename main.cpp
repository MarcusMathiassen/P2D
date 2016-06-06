//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

// --------------------------------- INCLUDES ---------------------------------

#include <iostream>								// cout
#include <GL/glew.h>							// GLEW setup.
#include <GLFW/glfw3.h>							// GLFW setup.

#include "Config.h"								// Global settings
#include "Inputs.h"								// User input
#include "Process.h"							// Updates all objects 
#include "Render.h"								// Renders all objects

int main()
{
	GLFWwindow* window;

	if (!glfwInit()) { std::cout << "GLFW INIT FAILED!\n"; }

	#ifdef MULTISAMPLING 
		glfwWindowHint(GLFW_SAMPLES, xMSAA); 
	#endif

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL);

	if (!glewInit()) { std::cout << "GLEW INIT FAILED!\n"; }

	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorEnterCallback(window, cursorEnterCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetKeyCallback(window, keyCallback);
	glEnable(GL_PROGRAM_POINT_SIZE);

	/* Enable multisampling */
	#ifdef MULTISAMPLING 
		glEnable(GL_MULTISAMPLE);
	#endif

	/* Make the window´s context current */
	glfwMakeContextCurrent(window);

    /* FOR FPS COUNTER */
	float lastTime = glfwGetTime();
   	int nbFrames = 0;

    while (!glfwWindowShouldClose(window)) {

		float currentTime = glfwGetTime();
		nbFrames++;
		if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
		 	if (showFPS) {
		    	printf("%f ms/frame\n", 1000/float(nbFrames));
		    }
		 	//dt = 1000/float(nbFrames);
		    nbFrames = 0;
		    lastTime++;  
		}

    	/* Keyboard, Mouse, Joystick */
		Inputs(window);

		/* Background color */
		glClearColor(BCKGRND.r,BCKGRND.g,BCKGRND.b,1);
		glClear(GL_COLOR_BUFFER_BIT);

		/* Tranform into pixel coordinates */
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);

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
			break;
	}

	/* Terminate window */
	glfwTerminate();

	return 0;
}

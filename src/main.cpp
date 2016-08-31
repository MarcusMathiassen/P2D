//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

// --------------------------------- INCLUDES ---------------------------------

#include <iostream>								// cout
#include <GL/glew.h>							// GLEW setup.
#include <GLFW/glfw3.h>							// GLFW setup.

#include "./Config/Config.h"					// Global settings
#include "./Process/Process.h"					// Updates all objects
#include "./Render/Render.h"					// Renders all objects
#include "./Utility/Color.h"					// Color
#include "./Utility/Inputs.h"					// User input
#include "./FixedGrid/FixedGrid.h"				// FixedGrid
#include "./Quadtree/Quadtree.h"				// Quadtree
#include "./Objects/Circle/Circle.h"			// Circle class

// ----------------------------------------------------------------------------

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

	if (use_fixedgrid) 		fixedgrid.init();
	if (use_quadtree) 		quadtree.reset();
}

static void glfwError(int id, const char* description)
{
  std::cout << description << std::endl;
}

int main()
{
	glfwSetErrorCallback(&glfwError);

	if (!glfwInit())
	{ 
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	#ifdef MULTISAMPLING
		glfwWindowHint(GLFW_SAMPLES, xMSAA);
	#endif

 	GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, APP_NAME, NULL, NULL);
 	if (window == nullptr)
 	{
 		std::cout << "Failed to create GLFW window." << std::endl;
 		glfwTerminate();
 		return -1;
 	}

 	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorEnterCallback(window, cursorEnterCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetKeyCallback(window, keyCallback);

	if (!glewInit())
	{ 
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/* Enable multisampling */
	#ifdef MULTISAMPLING
		glEnable(GL_MULTISAMPLE);
	#endif

	/* Make the window´s context current */
	glfwMakeContextCurrent(window);

   	/* Tranform into pixel coordinates */
   	int w,h;
   	glfwGetFramebufferSize(window,&w,&h);
   	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1, 1);
	screen_width = w;
   	screen_height = h;

	glClearColor(BCKGRND.r,BCKGRND.g,BCKGRND.b,1);

	/* FOR FPS COUNTER */
	float lastTime = glfwGetTime();
   	int nbFrames = 0;


   	if (use_fixedgrid) 	fixedgrid.init();
	if (use_quadtree) 	quadtree.reset();

// --------------------------------- LOOP -------------------------------------

    while (!glfwWindowShouldClose(window))
    {
		float currentTime = glfwGetTime();
		nbFrames++;

		if ( currentTime - lastTime >= 1.0 )
		{
			char title [256];
   			title [255] = '\0';
   			int numObj = static_cast<int>(object_vec.size());
    		snprintf ( title, 255,
       	          "%s %s - [FPS: %d] [OBJ: %d]",
       	            APP_NAME, APP_VERSION, nbFrames, numObj);

    		glfwSetWindowTitle(window, title);

		 	if (show_FPS) {
		    	//printf("\n%f ms/frame\n", 1000/float(nbFrames));
		    }
		    nbFrames = 0;
		    lastTime++;
		}

    	/* Keyboard, Mouse, Joystick */
		Inputs(window);

		glClear(GL_COLOR_BUFFER_BIT);


		// "Game" loop START
		update();
		draw();
		// "Game" loop END

		if (lock_FPS) {
			glfwSwapInterval(1);
		} else glfwSwapInterval(0);

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			break;
		}
	}

// ----------------------------------------------------------------------------

	/* Terminate window */
	glfwTerminate();

	return 0;
}

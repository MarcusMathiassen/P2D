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
#include "./SpatialHash/SpatialHash.h"			// SpatialHash
#include "./Quadtree/Quadtree.h"				// Quadtree
#include "./Objects/Circle/Circle.h"				// Circle class

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

	if (use_DynamicGrid) 	spatialHash.init();
	if (use_Quadtree) 		quadtree.reset();
}

int main()
{
	GLFWwindow* window;

	if (!glfwInit()) { std::cout << "GLFW INIT FAILED!\n"; }

	#ifdef MULTISAMPLING
		glfwWindowHint(GLFW_SAMPLES, xMSAA);
	#endif

	window = glfwCreateWindow(screen_width, screen_height, APP_NAME, NULL, NULL);

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

	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);

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


   	if (use_DynamicGrid) 	spatialHash.init();
	if (use_Quadtree) 		quadtree.reset();

// --------------------------------- LOOP -------------------------------------

    while (!glfwWindowShouldClose(window))
    {
    	#ifdef BENCHMARK
		int bLoop =  GetTimeMs64();
		#endif

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

		/* Background color */
		glClear(GL_COLOR_BUFFER_BIT);

		#ifdef BENCHMARK
		int bUpdate =  GetTimeMs64();
		#endif

		update();		// Updates all objects

		#ifdef BENCHMARK
		int aUpdate =  GetTimeMs64()-bUpdate;
		std::cout << "\n\n\n\nupdate():  " << aUpdate << " ms" << std::endl;
		#endif



		#ifdef BENCHMARK
		int bDraw =  GetTimeMs64();
		#endif

		draw();			// Draws all objects to screen




		#ifdef BENCHMARK
		int aDraw =  GetTimeMs64()-bDraw;
		std::cout << "draw():    " << aDraw << " ms" << std::endl;
		#endif


		/* Swap interval */
		if (lock_FPS) {
			glfwSwapInterval(1);
		} else glfwSwapInterval(0);


		#ifdef BENCHMARK
		std::cout << "Circles:   " << object_vec.size() << std::endl;
		#endif

		#ifdef BENCHMARK
		int aLoop =  GetTimeMs64()-bLoop;
		std::cout << "Total:     " << aLoop << " ms" << std::endl;
		#endif

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* ESC to quit */
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

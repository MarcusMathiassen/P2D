
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "Config.h"

extern const char APP_NAME[]     = "P2D";
extern const char APP_VERSION[]  = "0.6";
int screen_width = 512;					// Window width.
int screen_height = 512;				// Window height.
double xpos, ypos;						// Current mouse position.
double dt = 0.016667;					// Delta time

int numThreads = 8;						// Number of CPU threads
int uniGrid = 64;						// Number of grids.
int griduni = 2;
int comparisons = 0;					// Number of comparisons

bool use_pThread		= true;			// Use pThreads.

bool show_FPS 			= false;		// Show current FPS.
bool lock_FPS 			= true;			// lock FPS.

bool borderCol 			= true;			// Border collisions.
bool ballCol 			= true;			// Circle collisions.

bool use_Quadtree		= true;			// Quadtrees.
bool show_Quadtree		= false;			// Show quadtrees.

bool use_DynamicGrid	= false;		// Dynamic grid.
bool show_DynamicGrid	= false;			// Show dynamic grid.

bool slowmotion 		= false;		// Slows everything down.
bool gravity 			= false;		// Turn on/off gravity.
bool direction			= false;		// Turn on/off direciton.
bool gravForce 			= false;		// Turn on/off gravForce.

bool windowResized		= false;		// Check if window has been resized.
bool isInWindow			= true;			//


//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "Config.h"

const char WINDOW_NAME[] = "P2D_v0.6";	// Window name.
int screen_width = 512;					// Window width.
int screen_height = 512;				// Window height.
double xpos, ypos;						// Current mouse position.

int numThreads = 8;						// Number of CPU threads		   
int uniGrid = 4;						// Number of grids.		
int griduni = 0;
int comparisons = 0;					// Number of comparisons		
int numNodes = 0;						// Number of nodes

bool use_pThread		= true;			// Use pThreads.
			
bool show_FPS 			= false;		// Show current FPS.
bool lock_FPS 			= true;			// lock FPS.
			
bool borderCol 			= true;			// Border collisions.
bool ballCol 			= true;			// Circle collisions.
			
bool use_Quadtree		= false;		// Quadtrees.
bool show_Quadtree		= false;		// Show quadtrees.
			
bool use_DynamicGrid	= true;			// Dynamic grid.
bool show_DynamicGrid	= false;		// Show dynamic grid.
			
bool slowmotion 		= false;		// Slows everything down.
bool gravity 			= false;		// Turn on/off gravity.
bool direction			= false;		// Turn on/off direciton.
bool gravForce 			= false;		// Turn on/off gravForce.	
	
bool windowResized		= false;		// Check if window has been
										//  resized.

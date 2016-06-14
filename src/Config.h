
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#ifndef CONFIG_H
#define CONFIG_H

extern const char APP_NAME[];
extern const char APP_VERSION[];
extern int screen_width;					// Window width.
extern int screen_height;					// Window height.
extern double xpos, ypos;					// Current mouse position.

#define OPENMP								// Comment out to turn off.
											// (Slower than pThreads.)

#define BENCHMARK							// uncomment to get ms readings.

extern int numThreads;						// Number of CPU threads
extern int uniGrid;							// Number of grids.
extern int griduni;	
extern int comparisons;						// Number of comparisons
extern int numNodes;						// Number of nodes

#define MULTISAMPLING 						// Comment out to turn off.
#define xMSAA 4								// MSAA sampling.

#define ACCEL 9.81							// Acceleration(gravity).

extern bool use_pThread;					// Use pThreads.

extern bool show_FPS;						// Show current FPS.
extern bool lock_FPS;						// Unlock FPS.

extern bool borderCol;						// Border collisions.
extern bool ballCol;						// Circle collisions.

extern bool use_Quadtree;					// Quadtrees.
extern bool show_Quadtree;					// Show quadtrees.

extern bool use_DynamicGrid;				// Dynamic grid.
extern bool show_DynamicGrid;				// Show dynamic grid.

extern bool slowmotion;						// Slows everything down.
extern bool gravity;						// Turn on/off gravity.
extern bool direction;						// Turn on/off direciton.
extern bool gravForce;						// Turn on/off gravForce.		

extern bool windowResized;					// Check if window has been
											//  resized.

#endif
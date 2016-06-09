#include "Config.h"

const char WINDOW_NAME[]	= "P2D_v0.5";		// Window title name
int screen_width			= 512;				// Window width
int screen_height			= 512;				// Window height
double xpos, ypos;								// Mouse pos

int numThreads = 8;								// Number of threads
int uniBallSize = 10;                           // Universal ball size
int uniBallVert = 20;                           // Universal ball vertices.
int uniGrids = 4;								// Number of grids(min 4)

// Bools
bool use_pThread	= true;
bool showFPS 		= false;
bool unlockFPS 		= false;
bool borderCol 		= true;
bool ballCol 		= true;
bool useQuadtree	= false;
bool slowmotion 	= false;
bool gravity 		= false;
bool direction		= false;
bool gravForce 		= false;
bool gravForceCol 	= false;
bool drawQuadtrees	= false;
bool spawn          = false;
bool windowResized	= false;
#include "Config.h"

const char WINDOW_NAME[]	= "P2D_v0.6";		// Window title name
int screen_width			= 512;				// Window width
int screen_height			= 512;				// Window height
double xpos, ypos;								// Mouse pos

int numThreads = 8;								// Number of threads
int uniBallSize = 10;                           // Universal ball size
int uniBallVert = 20;                           // Universal ball vertices.
int uniGrid = 16;								// Number of grids(x4)
int comparisons = 0;							// Number of comparisons
int numNodes = 0;								// Number of nodes

// Bools
bool use_pThread	= true;
bool showFPS 		= false;
bool unlockFPS 		= false;
bool borderCol 		= true;
bool ballCol 		= true;
bool useQuadtree	= false;
bool showQuadtree	= false;
bool useDynaGrid	= true;
bool showDynaGrid	= true;
bool slowmotion 	= false;
bool gravity 		= false;
bool direction		= false;
bool gravForce 		= false;
bool gravForceCol 	= false;
bool drawQuadtrees	= false;
bool spawn          = false;
bool windowResized	= false;

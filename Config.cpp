#include "Config.h"
#include "Color.h"

const char WINDOW_NAME[]	= "P2D_v0.5";		// Window title name
const int WINDOW_WIDTH 		= 500;				// Window width
const int WINDOW_HEIGHT		= 500;				// Window height

int numThreads = 8;

const Color BCKGRND = white;					// Background color

// Bools
bool showFPS 		= false;
bool unlockFPS 		= false;
bool borderCol 		= true;
bool ballCol 		= true;
bool slowmotion 	= false;
bool gravity 		= false;
bool direction		= false;
bool gravForce 		= false;
bool gravForceCol 	= false;
bool drawQuadtrees	= false;
#ifndef CONFIG_H
#define CONFIG_H

#include "Color.h"

extern const char WINDOW_NAME[];				// Window name
extern const int WINDOW_WIDTH;					// Window width
extern const int WINDOW_HEIGHT;					// Window height

#define OPENMP									// Comment out to turn off.
												//  Currently slower than pThreads

extern int numThreads;							// Number of CPU threads

#define MULTISAMPLING 							// Comment out to turn off
#define xMSAA 4									// MSAA sampling

#define ACCEL 9.81								// Gravity

extern const Color BCKGRND;						// Background color

extern bool use_pThread;
extern bool showFPS;
extern bool unlockFPS;
extern bool borderCol;
extern bool ballCol;
extern bool useQuadtree;
extern bool slowmotion;
extern bool gravity;
extern bool direction;
extern bool gravForce;
extern bool gravForceCol;
extern bool drawQuadtrees;

#endif
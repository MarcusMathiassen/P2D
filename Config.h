#ifndef CONFIG_H
#define CONFIG_H

extern const char WINDOW_NAME[];			// Window name
extern int screen_width;					// Window width
extern int screen_height;					// Window height
extern double xpos, ypos;					// Mouse pos

#define OPENMP									// Comment out to turn off.
												//  Currently slower than pThreads

extern int numThreads;							// Number of CPU threads
extern int uniBallSize;
extern int uniBallVert;
extern int uniGrids;

#define MULTISAMPLING 							// Comment out to turn off
#define xMSAA 4									// MSAA sampling

#define ACCEL 9.81								// Gravity

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
extern bool spawn;
extern bool windowResized;

#endif
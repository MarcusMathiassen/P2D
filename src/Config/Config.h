
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <boost/format.hpp>

#include "../Utility/hwinfo.h"

extern std::string 							WINDOW_NAME;
extern int 									WINDOW_HEIGHT;
extern int 									WINDOW_WIDTH;
extern const std::string 					APP_NAME;
extern const std::string					APP_VERSION;
extern const std::string 					APP_AUTHOR;
extern std::string 							CPU_NAME;
extern int									CPU_CORES;
extern int									CPU_THREADS;
extern int 									xMSAA;
extern float 								gravity_accel;

extern bool 								MULTITHREADED;
extern std::map<std::string,std::string> 	list;
extern int 									screen_width;		// Window width.
extern int 									screen_height;		// Window height.
extern double 								xpos, ypos;			// Current mouse position.
extern double 								dt;
extern int 									numThreads;			// Number of CPU threads
extern int 									uniGrid;				// Number of grids.
extern int 									griduni;
extern int 									numNodes;			// Number of nodes
extern bool 								MULTISAMPLING; 		// Comment out to turn off.
extern bool 								debug_mode;			// Debug mode
extern bool 								use_pThread;		// Use pThreads.
extern bool 								show_FPS;			// Show current FPS.
extern bool 								lock_FPS;			// Unlock FPS.
extern bool 								borderCol;			// Border collisions.
extern bool 								ballCol;			// Circle collisions.
extern bool 								use_quadtree;		// Quadtrees.
extern bool 								use_fixedgrid;		// Fixed grid.
extern bool 								slowmotion;			// Slows everything down.
extern bool 								gravity;			// Turn on/off gravity.
extern bool 								direction;			// Turn on/off direciton.
extern bool 								gravForce;			// Turn on/off gravForce.
extern bool 								color_random;		// Random colors each time.
extern bool 								windowResized;		// Check if window has been resized.
extern bool 								isInWindow;

void print_config();
void create_file(const std::string& file_name);
bool parse_file(const std::string& file_name);
void setup_config();


#endif
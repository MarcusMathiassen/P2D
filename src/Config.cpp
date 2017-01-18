
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "Config.h"

// Default settings

std::string 					WINDOW_NAME 		= "P2D";
int 									WINDOW_HEIGHT 		= 512;
int 									WINDOW_WIDTH 		= 512;
const std::string 		APP_NAME 			= "P2D";
const std::string 		APP_VERSION 		= "0.7";
const std::string 		APP_AUTHOR 			= "Marcus Mathiassen";
std::string 					CPU_NAME 			= "";
int										CPU_CORES 			= 2;
int										CPU_THREADS 		= 4;
int 									xMSAA 				= 4;
float 								gravity_accel 		= 9.81;

bool 									MULTITHREADED 		= false;
bool 									debug_mode 			= false;
bool 									show_FPS 			= false;		// Show current FPS.
bool 									lock_FPS 			= true;			// lock FPS.
std::map<std::string, std::string> 		list;
int 									screen_width 		= WINDOW_WIDTH;	// Window width.
int 									screen_height 		= WINDOW_HEIGHT;// Window height.
double 								xpos, ypos;							// Current mouse position.
double 								dt 					= 0.016667;		// Delta time
int 									numThreads 			= CPU_THREADS;	// Number of CPU threads
int 									uniGrid				= 64;			// Number of grids.
int 									griduni				= 2;
bool									use_pThread			= true;			// Use pThreads.
bool									borderCol 			= true;			// Border collisions.
bool									ballCol 			= true;			// Circle collisions.
bool									use_quadtree		= true;			// Quadtrees.
bool									use_fixedgrid		= false;		// Fixed grid.
bool									slowmotion 			= false;		// Slows everything down.
bool									gravity 			= false;		// Turn on/off gravity.
bool									direction			= false;		// Turn on/off direciton.
bool									gravForce 			= false;		// Turn on/off gravForce.
bool									color_random 		= true; 		// Random colors each time.
bool									windowResized		= false;		// Check if window has been resized.
bool									isInWindow			= true;			//

void print_config()
{
	for(const auto& item : list)
	{
		 	std::cout << boost::format("%-20s %s\n") % (item.first+":") % item.second;
	}
}

void setup_config()
{
	CPU_NAME = get_cpu_brand();
	CPU_CORES = get_cpu_cores();
	CPU_THREADS = get_cpu_threads();
	numThreads = CPU_THREADS;

	screen_height = WINDOW_HEIGHT;
	screen_width = WINDOW_WIDTH;

	// If file can´t be found.
	if (!parse_file("config.txt")) create_file("config.txt");
	parse_file("config.txt");
	print_config();
}

void create_file(const std::string& file_name)
{
	std::cout << "Creating config file.." << std::endl;

	std::ofstream file (file_name);
	if (file)
	{
		file << "# This is a comment.\n";
		file << "# All comments and empty lines are ignored.\n";
		file << "# Delete file to reset to default settings.\n";

		file << "\n\n# Window settings(screen resolution)\n";
		file << boost::format("%-20s %s%s\n") % "WINDOW_NAME:" % WINDOW_NAME % ";";
		file << boost::format("%-20s %s%s\n") % "WINDOW_HEIGHT:" % WINDOW_HEIGHT % ";";
		file << boost::format("%-20s %s%s\n") % "WINDOW_WIDTH:" % WINDOW_WIDTH % ";";

		file << "\n\n# Application info\n";
		file << boost::format("%-20s %s%s\n") % "APP_NAME:" % APP_NAME % ";";
		file << boost::format("%-20s %s%s\n") % "APP_VERSION:" % APP_VERSION % ";";
		file << boost::format("%-20s %s%s\n") % "APP_AUTHOR:" % APP_AUTHOR % ";";

		file << "\n\n# CPU info (Changing number of threads may improve performance)\n";
		file << boost::format("%-20s %s%s\n") % "CPU_NAME:" % CPU_NAME % ";";
		file << boost::format("%-20s %s%s\n") % "CPU_CORES:" % CPU_CORES % ";";
		file << boost::format("%-20s %s%s\n") % "CPU_THREADS:" % CPU_THREADS % ";";

		file << "\n\n# Global variables (You may change these as you like)\n";
		file << boost::format("%-20s %s%s\n") % "xMSAA:" % xMSAA % ";";
		file << boost::format("%-20s %s%s\n") % "gravity_accel:" % gravity_accel % ";";
	}
}

bool parse_file(const std::string& file_name)
{
	if (!std::ifstream(file_name))  return false;

	std::ifstream file (file_name);

	if (file.is_open())				// Make sure our file can be opened
	{
		std::string line = "";

		while(std::getline (file,line))
		{
			if(line.length() == 0) 		// Skip blank lines
				continue;
			else if (line[0] == '#') 	// Skip comment lines
				continue;

			std::istringstream ss(line);
			std::string key;				// Holds the key
			std::string value;				// Holds the value

			ss >> std::ws;					// Remove any whitespace
			std::getline(ss, key,':');		// Get the key until ":"
			ss.get();						// Jump over the ":"
			ss >> std::ws;					// Remove any whitespace
			std::getline(ss,value, ';');	// Get value until ";"

			// Add to our map and clear the line.
			list.insert(std::pair<std::string, std::string>(key,value));
			line.clear();
		}

		WINDOW_NAME 			= list["WINDOW_NAME"];
		WINDOW_HEIGHT 		= std::stoi(list["WINDOW_HEIGHT"]);
		WINDOW_WIDTH 			= std::stoi(list["WINDOW_WIDTH"]);
		xMSAA             = std::stoi(list["xMSAA"]);
		gravity_accel 		= std::stof(list["gravity_accel"]);
		CPU_THREADS 			= std::stoi(list["CPU_THREADS"]);
	}

	return true;
}

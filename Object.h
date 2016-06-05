#ifndef _OBJECT_H
#define _OBJECT_H

#include <vector>

class Object {
private:

public:

	virtual void draw() const;		// Each object draws itself to screen.
	virtual void update();			// Each object is responsible of updating 
									//  its own members.
};

extern std::vector<std::unique_ptr<Object>> object_v;

#endif
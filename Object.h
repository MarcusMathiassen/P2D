#ifndef _OBJECT_H
#define _OBJECT_H

#include <memory>
#include <vector>

class Object {
private:

public:
	virtual void draw() const;
	virtual void update();	
							
};

extern std::vector<std::unique_ptr<Object>> object_vec;

#endif
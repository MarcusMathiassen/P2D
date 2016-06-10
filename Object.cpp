#include "Object.h"

void Object::draw() const {}	// Each object draws itself to screen.
void Object::update() {}		// Each object is responsible of updating 

std::vector<std::unique_ptr<Object>> object_vec;
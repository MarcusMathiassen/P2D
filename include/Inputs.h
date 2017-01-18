#ifndef INPUTS_H
#define INPUTS_H

#include <iostream>							// cout
#include <GLFW/glfw3.h>						// glfw

#include "Circle.h"		// Circle class
#include "Quadtree.h"			// Quadtree class
#include "FixedGrid.h"			// FixedGrid class
#include "Config.h"				// Global var, screen size, isInWindow
#include "Color.h"							// Color class
#include "Templates.h"						// vec, uptr

void Inputs(GLFWwindow* window);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos);
void cursorEnterCallback(GLFWwindow *window, int entered);
void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

#endif
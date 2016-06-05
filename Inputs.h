#ifndef INPUTS_H
#define INPUTS_H

#include <GLFW/glfw3.h>

void Inputs(GLFWwindow* window);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos);
void cursorEnterCallback(GLFWwindow *window, int entered);
void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

#endif
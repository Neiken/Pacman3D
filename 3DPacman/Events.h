#ifndef PACMAN_WINDOW_EVENTS
#define PACMAN_WINDOW_EVENTS

#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "Voxel.h"

extern GLFWwindow* Window;
extern int WindowWidth, WindowHeight, Wireframe, isMouseLocked;

void WindowStart();
void WindowDraw();
void WindowStop();

#endif
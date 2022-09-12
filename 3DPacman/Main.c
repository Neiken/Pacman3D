#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Events.h"

GLFWwindow* Window;
int WindowWidth = 1000, WindowHeight = 700, Wireframe = 0, isMouseLocked = 1; 

int main()
{
	if (!glfwInit()) { printf("\033[31mcouldn't initialize glfw\033[0m\n"); return 0; }

	Window = glfwCreateWindow(WindowWidth, WindowHeight, "3D Pacman", NULL, NULL);
	if (!Window) { printf("\033[31mcouldn't create window\033[0m\n"); return 0; }

	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPos(Window, WindowWidth / 2, WindowHeight / 2);

	glfwMakeContextCurrent(Window);
	gladLoadGL();

	WindowStart();

	int canChangeWireframeState = 1;

	while (!glfwWindowShouldClose(Window))
	{
		glfwPollEvents();

		if ((glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS && isMouseLocked) || (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !isMouseLocked))
		{
			glfwSetInputMode(Window, GLFW_CURSOR, (isMouseLocked ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED));
			isMouseLocked = !isMouseLocked;
		}

		if (!isMouseLocked) continue;

		glfwSwapBuffers(Window);

		if(glfwGetKey(Window, GLFW_KEY_E) == GLFW_PRESS && canChangeWireframeState)
		{
			glPolygonMode(GL_BACK, (Wireframe ? GL_FILL : GL_LINE));
			Wireframe = !Wireframe;
		}
		
		canChangeWireframeState = glfwGetKey(Window, GLFW_KEY_E) == GLFW_RELEASE;

		WindowDraw();
	}

	WindowStop();

	glfwDestroyWindow(Window);
	glfwTerminate();
}
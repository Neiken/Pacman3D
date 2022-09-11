#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Events.h"

//Referencia o 'extern GLFWwindow* Window' do "Events.c"
GLFWwindow* Window;

//Referencia o 'extern int WindowWidth, WindowHeight, Wireframe, isMouseLocked' do "Events.c"
int WindowWidth = 1000, WindowHeight = 700, Wireframe = 0, isMouseLocked = 1; 

int main()
{
	//Inicializa o GLFW e printa caso ocorra um erro
	if (!glfwInit()) { printf("\033[31mcouldn't initialize glfw\033[0m\n"); return 0; }

	//Cria uma janela com largura 'WindowWidth', altura 'WindowHeight' e nome '3D Pacman'
	//Imprime erro caso ocorra um erro na criaçao da janela
	Window = glfwCreateWindow(WindowWidth, WindowHeight, "3D Pacman", NULL, NULL);
	if (!Window) { printf("\033[31mcouldn't create window\033[0m\n"); return 0; }

	//glfwSetInputMode(Janela, TipoDoInput, NovoValor);
	//Faz o cursor ficar preso e invisivel dentro da janela
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Faz o cursor ficar no exato centro da janela
	glfwSetCursorPos(Window, WindowWidth / 2, WindowHeight / 2);

	//Poe todas as alteraçoes na janela 'Window'
	glfwMakeContextCurrent(Window);
	gladLoadGL();

	WindowStart(); //Roda alguns codigos no primeiro frame da janela

	int canChangeWireframeState = 1;

	//Executa enquanto a janela estiver aberta
	while (!glfwWindowShouldClose(Window))
	{
		glfwPollEvents(); //Processa os eventos da tela

		//Checa se a tecla 'ESC' foi apertada ou se o botao esquerdo do mouse foi apertado dentro da janela
		if ((glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS && isMouseLocked) || (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !isMouseLocked))
		{
			//Faz o cursor aparecer e nao ficar preso à tela ou desaparecer e ficar preso à tela
			glfwSetInputMode(Window, GLFW_CURSOR, (isMouseLocked ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED));
			isMouseLocked = !isMouseLocked;
		}

		//Permite o desenho da tela somente caso o mouse esteja travado
		if (!isMouseLocked) continue;

		glfwSwapBuffers(Window); //Troca os buffers, o buffer de desenho vira o buffer exibido e vice-versa

		//Checa se a tecla 'E' foi apertada, e só permite a execuçao dela uma unica vez por click
		if(glfwGetKey(Window, GLFW_KEY_E) == GLFW_PRESS && canChangeWireframeState)
		{
			//Ativa ou desativa o modo wireframe
			glPolygonMode(GL_BACK, (Wireframe ? GL_FILL : GL_LINE));
			Wireframe = !Wireframe;
		}
		
		canChangeWireframeState = glfwGetKey(Window, GLFW_KEY_E) == GLFW_RELEASE;

		WindowDraw(); //Roda alguns codigos a cada frame
	}

	WindowStop(); //Roda alguns codigos no ultimo frame antes da janela fechar

	glfwDestroyWindow(Window); //Deleta o ponteiro 'Window'
	glfwTerminate(); //Fecha o GLFW
}
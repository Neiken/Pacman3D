#include "Events.h"

Voxel voxel;

void WindowStart()
{
	glClearColor(0, 0.5f, 1, 1); //Faz a cor de fundo virar 'rgba(255, 127, 255, 255)'

	//Inicializa o voxel 'voxel'
	VoxelCreate(&voxel);
}

void WindowDraw() 
{
	glClear(GL_COLOR_BUFFER_BIT); //Pinta todos os pixeis com a cor de fundo

	//Desenha o voxel 'voxel'
	VoxelDraw(voxel);
}

void WindowStop() 
{
	//Deleta o voxel 'voxel'
	VoxelDestroy(&voxel);
}
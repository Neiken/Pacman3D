#include "Events.h"

Voxel voxel;

void WindowStart()
{
	glClearColor(0, 0.5f, 1, 1);

	VoxelCreate(&voxel);
}

void WindowDraw() 
{
	glClear(GL_COLOR_BUFFER_BIT);

	VoxelDraw(voxel);
}

void WindowStop() 
{
	VoxelDestroy(&voxel);
}
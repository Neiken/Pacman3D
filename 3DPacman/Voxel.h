#ifndef PACMAN_VOXEL_HEADER
#define PACMAN_VOXEL_HEADER

#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Voxel
{
	unsigned IndexCount;
	unsigned Program, VBO, VAO, IBO, VertexShader, FragmentShader;

	float Color[4];
	float Faces[6];
};
typedef struct Voxel Voxel;

static int CreateShader(int type, char* src);
static char* ReadFile(char* path);

void VoxelCreate(Voxel* voxel);
void VoxelDraw(Voxel voxel);
void VoxelDestroy(Voxel* voxel);

#endif
#include "Voxel.h"

void VoxelCreate(Voxel* voxel)
{
	voxel->VertexShader = CreateShader(GL_VERTEX_SHADER, ReadFile("Voxel.vert"));
	voxel->FragmentShader = CreateShader(GL_FRAGMENT_SHADER, ReadFile("Voxel.frag"));

	voxel->Program = glCreateProgram();
	glAttachShader(voxel->Program, voxel->VertexShader);
	glAttachShader(voxel->Program, voxel->FragmentShader);
	glLinkProgram(voxel->Program);

	float vertexs[] =
	{
		-.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, -.5f, 0.5f,
		-.5f, -.5f, 0.5f,

		-.5f, 0.5f, -.5f,
		0.5f, 0.5f, -.5f,
		0.5f, -.5f, -.5f,
		-.5f, -.5f, -.5f
	};

	unsigned char indexs[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	voxel->IndexCount = sizeof(indexs) / sizeof(unsigned char);

	glGenVertexArrays(1, &(voxel->VAO));
	glBindVertexArray(voxel->VAO);

	glGenBuffers(1, &(voxel->VBO));
	glBindBuffer(GL_ARRAY_BUFFER, voxel->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &(voxel->IBO));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, voxel->IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexs), indexs, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VoxelDraw(Voxel voxel)
{
	glBindVertexArray(voxel.VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, voxel.IBO);
	glUseProgram(voxel.Program);

	glDrawElements(GL_TRIANGLES, voxel.IndexCount, GL_UNSIGNED_BYTE, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VoxelDestroy(Voxel* voxel)
{
	glDeleteShader(voxel->VertexShader); 
	glDeleteShader(voxel->FragmentShader);
	glDeleteProgram(voxel->Program);
	glDeleteBuffers(1, &(voxel->VBO));
	glDeleteBuffers(1, &(voxel->IBO));
	glDeleteVertexArrays(1, &(voxel->VAO));
}

static int CreateShader(int type, char* src)
{
	int shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	int success; glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		int value; glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &value);

		char* log = calloc(value + 1, sizeof(char));
		glGetShaderInfoLog(shader, value, NULL, log);

		printf("\033[31merror:\n\n\033[33m%s\n\n\033[31m%s\033[0m\n", src, log);

		free(log);
		memset(log, 0, sizeof(char) * (value + 1));

		goto _freeSrc;

		glDeleteShader(shader);
		return -1;
	}

	goto _freeSrc;

	return shader;

_freeSrc:
	free(src);
	memset(src, 0, sizeof(char) * (strlen(src) + 1));
}

static char* ReadFile(char* path)
{
	FILE* file; fopen_s(&file, path, "r");
	if (!file) { printf("\033[31mno file '%s'\033[0m\n", path); return NULL; }

	fseek(file, 0, SEEK_END);
	unsigned size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* content = calloc(size + 1, sizeof(char));
	fread(content, sizeof(char), size, file);

	fclose(file);

	return content;
}
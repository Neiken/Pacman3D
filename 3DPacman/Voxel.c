#include "Voxel.h"

void VoxelCreate(Voxel* voxel)
{
	//Cria um shader do tipo 'Vertex Shader' com o codigo dentro do arquivo 'Voxel.vert'
	voxel->VertexShader = CreateShader(GL_VERTEX_SHADER, ReadFile("Voxel.vert"));

	//Cria um shader do tipo 'Fragment Shader' com o codigo dentro do arquivo 'Voxel.frag'
	voxel->FragmentShader = CreateShader(GL_FRAGMENT_SHADER, ReadFile("Voxel.frag"));

	voxel->Program = glCreateProgram(); //Cria um programa(junçao de todos os shaders que voce por)

	//Poe o VertexShader dentro do programa
	glAttachShader(voxel->Program, voxel->VertexShader);

	//Poe o FragmentShader dentro do programa
	glAttachShader(voxel->Program, voxel->FragmentShader);

	//Junta todos os shaders dentro do programa em um só
	glLinkProgram(voxel->Program);

	//Vertices
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

	//Indices dos triangulos
	unsigned char indexs[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	//Armazena a quantidade de indices dentro da variavel 'IndexCount'
	voxel->IndexCount = sizeof(indexs) / sizeof(unsigned char);

	//Cria um handle de VertexArrayObject(armazena informaçoes sobre as vertices) e armazena na variavel 'VAO'
	glGenVertexArrays(1, &(voxel->VAO));

	//Faz o opengl usar a VAO receber quaisquer modificaçoes que forem feitas depois dessa chamada
	glBindVertexArray(voxel->VAO);

	//Cria um handle de buffer e armazena na variavel 'VBO'
	glGenBuffers(1, &(voxel->VBO));

	//Faz a variavel 'GL_ARRAY_BUFFER' receber o buffer 'VBO'
	glBindBuffer(GL_ARRAY_BUFFER, voxel->VBO);

	//glBufferData(buffer, tamanho da array, array, tipo do buffer)
	//O tipo de buffer 'GL_STATIC_DRAW' indica que o buffer só vai receber um unico valor
	//Que nao será modificado
	//Poe a array 'vertexs' como valor do buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);

	//glVertexAttribPointer(posiçao do atributo, quantidade de vertices, tipo das vertices, normarlizar vertices, tamanho em bytes de cada vertice, offset)
	//Define informaçoes sobre os valores a serem colocados no atributo(attribute)
	//aVertexPosition, por ele ser o primeiro atributo declarado, ele possui a posiçao '0'
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0); //Atribui os valores no atributo de posiçao '0'(aVertexPosition)

	//IndexBufferObject
	glGenBuffers(1, &(voxel->IBO));

	//Faz a variavel 'GL_ELEMENT_ARRAY_BUFFER' receber o buffer IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, voxel->IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexs), indexs, GL_STATIC_DRAW);

	//Desativando os buffers e a VAO para evitar que sejam modificadas sem sabermos
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VoxelDraw(Voxel voxel)
{
	glBindVertexArray(voxel.VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, voxel.IBO);
	glUseProgram(voxel.Program); //Define como desenhar os objetos

	//Desenha as informçacoes dentro da VAO com os indices da variavel 'GL_ELEMENT_ARRAY_BUFFER'
	glDrawElements(GL_TRIANGLES, voxel.IndexCount, GL_UNSIGNED_BYTE, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VoxelDestroy(Voxel* voxel)
{
	glDeleteShader(voxel->VertexShader); 
	glDeleteShader(voxel->FragmentShader);
	glDeleteProgram(voxel->Program); //Deleta o programa
	glDeleteBuffers(1, &(voxel->VBO)); //Deleta a VBO
	glDeleteBuffers(1, &(voxel->IBO)); //Deleta a IBO
	glDeleteVertexArrays(1, &(voxel->VAO)); //Deleta a VAO
}

static int CreateShader(int type, char* src)
{
	int shader = glCreateShader(type); //Cria um handle pro shader 
	glShaderSource(shader, 1, &src, NULL); //Atribui o codigo 'src' dentro do shader
	glCompileShader(shader); //Compila o shader

	//Pega o resultado da compilaçao do shader e poe na variavel 'success'
	int success; glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	
	//Checa se a compilaçao deu errado
	if (!success)
	{
		int value;

		//Pega o tamanho do log do erro e armazena na variavel 'value'
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &value);

		//Aloca uma string de tamanho 'value + 1' no heap
		char* log = calloc(value + 1, sizeof(char));

		//Pega 'value' caracteres do log do erro do shader e poe na string 'log'
		glGetShaderInfoLog(shader, value, NULL, log);

		//Imprime o codigo que deu erro e o erro
		printf("\033[31merror:\n\n\033[33m%s\n\n\033[31m%s\033[0m\n", src, log);

		//Libera a memoria do heap
		free(log);
		memset(log, 0, sizeof(char) * (value + 1));

		//Libera o ponteiro 'src'
		goto _freeSrc;

		//Deleta o handle do shader
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
	FILE* file; fopen_s(&file, path, "r"); //Abre o arquivo 'path'

	//Checa se o arquivo existe
	if (!file) { printf("\033[31mno file '%s'\033[0m\n", path); return NULL; }

	//Transporta o index do caractere atual para o final do arquivo
	fseek(file, 0, SEEK_END);

	//Retorna o index do caractere atual, no caso o index do ultimo caractere
	//Ou seja, a quantidade de caracteres do arquivo
	unsigned size = ftell(file);

	//Transporta o index do caractere atual para o inicio do arquivo
	fseek(file, 0, SEEK_SET);

	//Aloca uma string de tamanho 'size + 1' no heap
	char* content = calloc(size + 1, sizeof(char));

	//fread(buffer, tamanho de cada elemento a ser lido, quantidade de elementos a serem lidos, arquivo)
	//Pega todo o conteudo do arquivo e poe na string 'content'
	fread(content, sizeof(char), size, file);

	//Libera o ponteiro
	fclose(file);

	return content;
}
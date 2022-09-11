attribute vec3 aVertexPosition; //Variavel que vai receber a posiçao de cada vertice

void main()
{
	//Vai atribuir a posiçao de cada vertice à variavel do opengl 'gl_Position'
	//Essa variavel TEM que receber a posiçao final da vertice
	gl_Position = vec4(aVertexPosition, 1);
}
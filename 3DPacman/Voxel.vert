attribute vec3 aVertexPosition; //Variavel que vai receber a posi�ao de cada vertice

void main()
{
	//Vai atribuir a posi�ao de cada vertice � variavel do opengl 'gl_Position'
	//Essa variavel TEM que receber a posi�ao final da vertice
	gl_Position = vec4(aVertexPosition, 1);
}
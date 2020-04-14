#version 110


// Рабочий код
//attribute vec3 position;
//attribute vec4 color;
//attribute vec3 normal;
//attribute vec3 texcoord0;

//uniform vec4 constColor;
//uniform mat4 matrixWorldViewProjT;

//varying vec2 uv1; // текстурные коорд которые были в вершине - передаём во фрагмент шейдер
//varying float texture_flag;


//void main()
//{
//	gl_Position		= vec4(position, 1.0) * matrixWorldViewProjT;
//	gl_FrontColor	= color * constColor;
//	uv1				= texcoord0.xy;

//	texture_flag = 0.0f;
	
//}

attribute vec3 position;
attribute vec4 color;
attribute vec3 normal;
attribute vec3 texcoord0;

uniform vec4 constColor;
uniform mat4 matrixWorldViewProjT;

varying vec2 uv1; // текстурные коорд которые были в вершине - передаём во фрагмент шейдер
varying float texture_flag;


void main()
{
	gl_Position		= vec4(position, 1.0) * matrixWorldViewProjT;
	gl_FrontColor	= color * constColor;
	uv1				= texcoord0.xy;


	texture_flag = 0.0;
	if(gl_Position.x > 0.0) // (1!=1)
	{
		texture_flag = 1.0;
	}

	/*if(gl_Position.x > 0.0) // (1!=1)
	{
		texture_flag = 1.0;
	}*/

	
	
}
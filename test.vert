
// GLSL         OpenGL 
// 1.10         2.0
varying 		vec4 fragColor;
varying  	vec2 fragCoord;

void main()
{
	gl_Position 	= gl_Vertex;
	fragCoord	= gl_Position.xy;
}
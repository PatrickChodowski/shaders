

// Vertex shader exists to put the value of gl_Position
// it uses projectionMatrix, ModelView Matrix and position of the vertex to do it

// built in vertex shader variables:
// gl_ModelViewMatrix;
// gl_ProjectionMatrix;
// gl_Vertex;
// gl_Normal;
// gl_Color;
// gl_ModelViewProjectionMatrix;
// gl_Position;

// vertex is to be transformed by the model view and projection 
// matrices using the following equation


// uniform variables remain constant along frame/scene
// can be read and not written in both vertex and fragment

// the matrices are provided through predefined uniforma variables declared as :
// dont need to be redeclared?
// uniform mat4 gl_ModelViewMatrix;
// uniform mat4 gl_ProjectionMatrix;
// uniform mat4 gl_ModelViewProjectionMatrix;

// access incoming vertex. Vertices are supplied one by one to the vertex shader through this:
// attribute vec4 gl_Vertex;

// in order to output transformed vertex, 
// shader must write to the gl_Position as well, declared as vec4
// gl_Position is gl_Vertex after it has been transformed
// by the modelview matrix and the projection matrix
uniform mat4 gpu_ModelViewProjectionMatrix;
uniform vec2 resolution;
attribute vec3 gpu_Vertex;
attribute vec2 gpu_TexCoord;
varying vec2 texCoord;
varying vec3 vertex;

void main(void)
{
  texCoord = vec2(gpu_TexCoord);
  vertex = vec3(gpu_Vertex);
  gl_Position = gpu_ModelViewProjectionMatrix * vec4(gpu_Vertex, 1.0);

}
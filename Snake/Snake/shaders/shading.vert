uniform vec3 lightPos;

varying vec3 lVec;
varying vec3 norm;
varying vec3 vertex;
varying vec4 color;
varying vec4 texcolor;

void main(){
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    vertex = gl_ModelViewMatrix * gl_Vertex;
    lVec = lightPos;// - gl_Vertex.xyz;
    norm = gl_Normal;
    color = gl_Color;
}

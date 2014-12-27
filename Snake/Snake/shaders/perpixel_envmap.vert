
varying vec4 R_world;

uniform mat4 view_matrix;
uniform vec4 camera_world;

void main(void)
{
   vec4 V_world = normalize(camera_world - gl_ModelViewMatrix * gl_Vertex);
   vec4 N_world = vec4(normalize(gl_NormalMatrix * gl_Normal), 1.0);
   R_world = reflect(-V_world, N_world);

   gl_TexCoord[0] = gl_MultiTexCoord0;
   gl_Position = gl_ProjectionMatrix * view_matrix * gl_ModelViewMatrix * gl_Vertex;
}


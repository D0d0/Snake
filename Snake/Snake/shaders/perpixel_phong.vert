varying vec4 V_eye;
varying vec4 L_eye;
varying vec4 N_eye;

void main(void)
{
   V_eye = gl_ModelViewMatrix * gl_Vertex;
   L_eye = gl_LightSource[0].position - V_eye;
   N_eye = vec4(gl_NormalMatrix * gl_Normal, 0.0);
   V_eye = -V_eye;

   gl_TexCoord[0] = gl_MultiTexCoord0;
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}


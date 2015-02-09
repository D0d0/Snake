void main(void)
{
   vec4 V_eye = gl_ModelViewMatrix * gl_Vertex;
   vec4 L_eye = gl_LightSource[0].position - V_eye;
   vec4 N_eye = vec4(gl_NormalMatrix * gl_Normal, 0.0);
   V_eye = -V_eye;
   
   V_eye = normalize(V_eye);
   L_eye = normalize(L_eye);
   N_eye = normalize(N_eye);

   float diffuse = clamp(dot(L_eye, N_eye), 0.0, 1.0);
   vec4 R_eye = reflect(-L_eye, N_eye);
   float specular = sign(diffuse) * pow(clamp(dot(R_eye, V_eye), 0.0, 1.0), 32.0);

   vec4 color = (vec4(0.2, 0.2, 0.2, 1.0) + gl_LightSource[0].ambient) * gl_FrontMaterial.ambient;
   color += diffuse * gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse;
   color += specular * gl_LightSource[0].specular * gl_FrontMaterial.specular;

   gl_FrontColor = color;
   gl_BackColor = color;
   gl_TexCoord[0] = gl_MultiTexCoord0;
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
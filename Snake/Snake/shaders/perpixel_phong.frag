varying vec4 V_eye;
varying vec4 L_eye;
varying vec4 N_eye;

uniform sampler2D color_texture;
uniform int texturing_enabled;
uniform int lighting_enabled;

void main(void)
{
   vec4 V = normalize(V_eye);
   vec4 L = normalize(L_eye);
   vec4 N = normalize(N_eye);

   float diffuse = clamp(dot(L, N), 0.0, 1.0);
   vec4 R = reflect(-L, N);
   float specular = sign(diffuse) * pow(clamp(dot(R, V), 0.0, 1.0), 32.0);

   vec4 diffuse_material = gl_FrontMaterial.diffuse;
   if (texturing_enabled > 0)
       diffuse_material = texture2D(color_texture, gl_TexCoord[0].st);
	   
   vec4 color = diffuse_material;
   if (lighting_enabled > 0)
   {
	   color = (vec4(0.2, 0.2, 0.2, 1.0) + gl_LightSource[0].ambient) * gl_FrontMaterial.ambient;
	   color += diffuse * gl_LightSource[0].diffuse * diffuse_material;
	   color += specular * gl_LightSource[0].specular * gl_FrontMaterial.specular;
   }

   gl_FragColor = color;
}

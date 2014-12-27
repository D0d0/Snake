varying vec4 R_world;

uniform sampler2D color_texture;
uniform samplerCube cubemap_texture;
uniform int texturing_enabled;

void main(void)
{
   vec3 R = normalize(R_world.yzx);
   vec4 color = textureCube(cubemap_texture, R);

   if (texturing_enabled > 0)
       color = mix(color, texture2D(color_texture, gl_TexCoord[0].st), 0.5f);

   gl_FragColor = color;
}

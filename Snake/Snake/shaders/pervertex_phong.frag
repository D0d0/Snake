uniform sampler2D color_texture;
uniform int texturing_enabled;

void main(void)
{
   gl_FragColor = gl_Color;
   if (texturing_enabled > 0)
       gl_FragColor = gl_FragColor * texture2D(color_texture, gl_TexCoord[0].st);
}

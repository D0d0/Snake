uniform sampler2D texture_color;
varying vec4 color;

float random(vec2 x){
    int n = int(x.x * 40.0 + x.y * 6400.0);
    n = (n << 13) ^ n;
    float r = 1.0 - float( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) * (1.0 / 1073741824.0);

    return r * 0.5 + 0.5;
}
float rand(vec2 n){
  return 0.5 + 0.5 * fract(sin(dot(n.xy, vec2(12.9898, 78.233)))* 43758.5453);
}
void main(){
   vec4 sum = vec4(0);
   vec4 sumColor = vec4(0);
   vec2 texcoord = vec2(gl_TexCoord[0].st);
   int j;
   int i;
   gl_FragColor = color;
   if(texcoord != 0){
       gl_FragColor = texture2D(texture_color ,texcoord);
   }

   gl_FragColor = rand(texcoord)*gl_FragColor;
}

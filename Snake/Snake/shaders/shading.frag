uniform sampler2D texture_color;
uniform bool skybox;

varying vec3 lVec;
varying vec3 norm;
varying vec4 color;
varying vec4 texcolor;
varying vec3 vertex;

vec3 reflect(vec3 N, vec3 L){
   return 2.0*N*dot(N, L) - L;
}

void main(){
	vec3 lightVec = normalize(lVec);
	vec3 normVec = normalize(norm);
  vec3 vertexVec = normalize(vertex);
  float diffuse = clamp(dot(lightVec, normVec),0.0,1.0);
  vec3 R = reflect(normVec, lightVec);
  float specular =  pow( max( 0.0, dot( vertexVec, R )), 32 );      
  if(skybox){
		specular = 0.0;
  }
  gl_FragColor = texture2D(texture_color, gl_TexCoord[0].st)*diffuse*0.5 + color*diffuse*0.5 + specular*color;
}

varying vec3 cube_map_coords;
void main(void)
{
   cube_map_coords = gl_Vertex.xzy;
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}


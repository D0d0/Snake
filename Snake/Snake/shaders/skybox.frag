uniform samplerCube cube_map;
varying vec3 cube_map_coords;

void main(void)
{
   gl_FragColor = textureCube(cube_map, cube_map_coords);
}

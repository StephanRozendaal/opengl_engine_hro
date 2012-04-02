#version 120
uniform	mat4 mwvp_matrix;
attribute vec3 attrib_vertex;
attribute vec3 attrib_normal;
void main() {
  gl_Position = mwvp_matrix * vec4( attrib_vertex, 1);
}
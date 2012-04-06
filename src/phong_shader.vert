#version 120

uniform	mat4 mvp_matrix;
uniform mat4 mv_matrix;
uniform mat3 normalmatrix;
uniform vec3 vlightposition;

attribute vec3 attrib_vertex;
attribute vec3 attrib_normal;

varying vec3 vvaryingnormal;
varying vec3 vvaryinglightdir;

void main() {
  vvaryingnormal = normalmatrix * attrib_normal;
  vec4 vposition4 = mv_matrix * vec4(attrib_vertex, 1.0);
  vec3 vposition3 = vposition4.xyz / vposition4.w;
  vvaryinglightdir = normalize(vlightposition - vposition3);
  gl_Position = mvp_matrix * vec4(attrib_vertex, 1);
}
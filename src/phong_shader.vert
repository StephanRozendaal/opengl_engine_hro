#version 120

uniform	mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform mat3 normal_matrix;
uniform vec4 light_position;
uniform vec3 camera_position;

attribute vec3 attrib_vertex;
attribute vec3 attrib_normal;

varying vec3 vvaryingnormal;
varying vec3 vvaryinglightdir;

void main() {
  vvaryingnormal = normal_matrix * attrib_normal;
  //vec4 transformed_vertex = normalize(vec4((attrib_vertex - camera_position),1.0));
  // vec4 light_vector = transformed_vertex - light_position;
  // view = normalize(camera_position - transformed_vertex.xyz);
  vec4 vposition4 = view_matrix * model_matrix * vec4(attrib_vertex, 1.0);
  vec3 vposition3 = vposition4.xyz / vposition4.w;
  vvaryinglightdir = normalize(light_position.xyz - vposition3);
  gl_Position = projection_matrix * view_matrix * model_matrix * vec4(attrib_vertex, 1.0);
}

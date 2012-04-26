#version 120

attribute vec3 attrib_vertex;
attribute vec3 attrib_normal;

uniform vec4 camera_position;
uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform mat3 normal_matrix;

varying vec4 position; // vertex position.
varying vec3 vnormal_direction;
varying vec4 vcamera_position;

void main() {
  vcamera_position = view_matrix * model_matrix * vec4(attrib_vertex, 1.0);
  position = model_matrix * vec4(attrib_vertex, 1.0);
  vnormal_direction = normal_matrix * attrib_normal;
  gl_Position = projection_matrix * view_matrix * model_matrix * vec4(attrib_vertex, 1.0);
} 

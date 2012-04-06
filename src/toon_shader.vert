#version 120

attribute vec3 attrib_vertex;
attribute vec3 attrib_normal;

varying float texture_coordinate; // smooth?

uniform vec3 light_position;
uniform mat4 mvp_matrix;
uniform mat4 mv_matrix;
uniform mat3 normal_matrix;

void main() {
  vec3 v_eye_normal = normal_matrix * attrib_normal;
  vec4 v_position_4 = mv_matrix * vec4(attrib_vertex, 1.0);
  vec3 v_position_3 = v_position_4.xyz / v_position_4.w;
  vec3 light_dir = normalize(light_position - v_position_3);
  texture_coordinate = max(0.0, dot(v_eye_normal, light_dir));

  gl_Position = mvp_matrix * vec4(attrib_vertex, 1.0);
} 

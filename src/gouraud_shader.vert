#version 120

attribute vec3 attrib_vertex;
attribute vec3 attrib_normal;

//uniform vec4 ambient_color;
//uniform vec4 diffuse_color;
//uniform vec4 specular_color;

uniform vec4 light_position;
uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform mat3 normal_matrix;

varying float specular_intensity;
varying float diffuse_intensity;

void main() {
  vec4 vertex_position_camera= view_matrix * model_matrix * vec4(attrib_vertex, 1.0);
  vec3 normal_camera = normalize(normal_matrix * attrib_normal);
  vec4 light_position_camera = view_matrix * model_matrix * light_position;
  vec3 light_vert = normalize(vec3(light_position_camera - vertex_position_camera));
  vec3 light_refl = normalize(reflect(light_vert, normal_camera));
  diffuse_intensity = max(dot(light_vert, normal_camera), 0.0);
  specular_intensity = max(dot(light_refl, normalize(vec3(vertex_position_camera))), 0.0);
  specular_intensity = pow(specular_intensity, 6.0);
  gl_Position = projection_matrix * view_matrix * model_matrix * vec4(attrib_vertex, 1.0);
}

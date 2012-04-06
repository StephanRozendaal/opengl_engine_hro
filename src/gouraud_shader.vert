#version 120

attribute vec3 attrib_vertex;
attribute vec3 attrib_normal;

uniform vec4 ambient_color;
uniform vec4 diffuse_color;
uniform vec4 specular_color;

uniform vec3 light_position;
uniform mat4 mvp_matrix;
uniform mat4 mv_matrix;
uniform mat3 normal_matrix;

varying vec4 varying_color;

void main() {
  vec3 v_eye_normal = normal_matrix * attrib_normal;
  vec4 v_position_4 = mv_matrix * vec4(attrib_vertex, 1.0);
  vec3 v_position_3 = v_position_4.xyz / v_position_4.w;
  vec3 v_lightdir = normalize(light_position - v_position_3);
  float diff = max(0.0, dot(v_eye_normal, v_lightdir));
  varying_color = diff * diffuse_color;
  varying_color += ambient_color;
  vec3 v_reflection = normalize(reflect(-v_lightdir, v_eye_normal));
  float spec = max(0.0, dot(v_eye_normal, v_reflection));
  if( diff != 0) {
    float f_spec = pow(spec, 128.0);
    varying_color.rgb += vec3(f_spec, f_spec, f_spec);
  }

  gl_Position = mvp_matrix * vec4(attrib_vertex, 1.0);
}

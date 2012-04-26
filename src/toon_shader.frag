#version 120

uniform vec4 light_position;
uniform vec4 ambient_color;
uniform vec4 diffuse_color;
uniform vec4 specular_color;

varying vec4 position;
varying vec3 vnormal_direction;
varying vec4 vcamera_position;

void main() {
  float shininess = 2;
  float diffuse_threshold = 0.1;
  vec3 normal_direction = normalize(vnormal_direction);
  vec3 view_direction = normalize(vcamera_position.xyz - position.xyz);
  vec3 light_direction;
  float attenuation = 1.0;
  light_direction = normalize(light_position.xyz);
  vec3 fragment_color = vec3(ambient_color);
  //diffuse illumination
  if(attenuation * max(0.0, dot(normal_direction, light_direction)) > diffuse_threshold) {
    fragment_color = vec3(diffuse_color);
  }
  //highlights
  if(dot(normal_direction, light_direction) > 0.0 && attenuation * pow(max(0.0, dot(reflect(-light_direction, normal_direction),view_direction)), shininess) > 0.5) {
    fragment_color = specular_color.a * diffuse_color.rgb * specular_color.rgb + (1.0 - specular_color.a) * fragment_color;
  }
  gl_FragColor = vec4(fragment_color, 1.0);
}

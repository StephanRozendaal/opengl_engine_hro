#version 120
uniform vec4 ambient_color;
uniform vec4 diffuse_color;
uniform vec4 specular_color;
//varying vec4 varying_color; // smooth?
varying float specular_intensity;
varying float diffuse_intensity;
void main() {
  gl_FragColor = ambient_color + diffuse_color * diffuse_intensity + specular_color * specular_intensity;
}

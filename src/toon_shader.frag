#version 120

uniform sampler1D color_table;
varying float texture_coordinate;

void main() {
  gl_FragColor = texture(color_table, texture_coordinate);
}

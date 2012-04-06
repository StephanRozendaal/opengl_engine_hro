#version 120

uniform vec4 ambient_color;
uniform vec4 diffuse_color;
uniform vec4 specular_color;

varying vec3 vvaryingnormal;
varying vec3 vvaryinglightdir;

void main() {
  float diff = max(0.0, dot(normalize(vvaryingnormal), normalize(vvaryinglightdir)));
  gl_FragColor = diff * diffuse_color;
  gl_FragColor += ambient_color;
  vec3 vreflection = normalize(reflect(-normalize(vvaryinglightdir), 
  normalize(vvaryingnormal)));
  float spec = max(0.0, dot(normalize(vvaryingnormal), vreflection));
  
  if(diff != 0 ) {
  	float fSpec = pow(spec, 128.0);
  	gl_FragColor.rgb += vec3(fSpec, fSpec, fSpec);
  	}
}
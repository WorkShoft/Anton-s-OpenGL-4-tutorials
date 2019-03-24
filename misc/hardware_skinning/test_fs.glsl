#version 410

uniform sampler2D texture1;
in vec3 colour;
in vec3 normal;
in vec2 st;
out vec4 frag_colour;

void main() {
  vec4 texel_a = texture (texture1, st);
  frag_colour = texel_a;
  //frag_colour = vec4(colour, 1.0);
}

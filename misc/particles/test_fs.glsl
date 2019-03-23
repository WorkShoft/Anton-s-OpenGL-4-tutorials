/* shader to render simple particle system points */
#version 410 core

in float opacity;
uniform sampler2D tex; // optional. enable point-sprite coords to use
uniform vec4 colours;
out vec4 frag_colour;

vec4 particle_colour = colours;


void main () {
	// using point texture coordinates which are pre-defined over the point
	vec4 texel = texture (tex, gl_PointCoord);
	frag_colour.a = opacity * texel.a;
	frag_colour.rgb = particle_colour.rgb * texel.rgb;
}

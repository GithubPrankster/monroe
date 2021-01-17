#version 460 core
out vec4 frag;

in vec2 ruv;

uniform sampler2D tex;

void main()
{
	frag = texture(tex, ruv);
}

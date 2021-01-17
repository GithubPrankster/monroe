#version 460 core
out vec4 frag;

in vec2 ruv;

uniform sampler2D tex;

const int mat[16] = int[16] (
	-4, 0, -3, 1,
	2, -2, 3, -1,
	-3, 1, -4, 0,
	3, -1, 2, -2
);

// Note: Based off emulator PS1 GPU code
// It's widespread enough you need to only look at your favorite one's
vec3 dither(vec3 col, uvec4 fc)
{
	ivec3 uncol = ivec3(col * 255.999) + mat[(fc.y & 3u) * 4u + (fc.x & 3u)];
	uncol = clamp(uncol, ivec3(0), ivec3(255));
	return vec3(uncol) / 255.999;
}

// I have no need for anything under/around 15-bit
// If higher, only 24-bit, and at that point just disable
// it lol
vec4 band_color(vec4 col)
{
	const vec4 depth = vec4(vec3(15.0), 6.0);
	return floor(col * depth) / depth;
}

void main()
{
	vec4 col = texture(tex, ruv);

	// TODO: Blend modes (software side)

	// Checking emulator behavior, dither occurs before banding
	// So it's kino
	col.rgb = dither(col.rgb, uvec4(gl_FragCoord));
	col = band_color(col);

	frag = col;
}

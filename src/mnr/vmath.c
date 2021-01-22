#include "mnr/vmath.h"

void mat4_ortho(mat4 M, float l, float r, float b, float t, float n, float f)
{
	M[0] = 2.f / (r - l);
	mat4a(M, 0, 1) = mat4a(M, 0, 2) = mat4a(M, 0, 3) = 0.f;

	mat4a(M, 1, 1) = 2.f / (t - b);
	mat4a(M, 1, 0) = mat4a(M, 1, 2) = mat4a(M, 1, 3) = 0.f;

	mat4a(M, 2, 2)= -2.f / (f - n);
	mat4a(M, 2, 0) = mat4a(M, 2, 1) = mat4a(M, 2, 3) = 0.f;

	mat4a(M, 3, 0) = -(r + l) / (r - l);
	mat4a(M, 3, 1) = -(t + b) / (t - b);
	mat4a(M, 3, 2) = -(f + n) / (f - n);
	mat4a(M, 3, 3) = 1.f;
}

void mat4_scale(mat4 M, const vec3 s)
{
	for(int i = 0; i < 3; ++i)
		mat4a(M, i, i) = s[i];
}

void mat4_translate(mat4 M, const vec3 s)
{
	for(int i = 0; i < 3; ++i)
		mat4a(M, 3, i) = s[i];
}

void mat4_translate_forward(mat4 M, const vec3 s)
{
	for(int i = 0; i < 3; ++i)
		mat4a(M, 3, i) += s[i];
}

int sign(int x)
{
	return (x >> SIGN_BIT) | ((unsigned)-x >> SIGN_BIT);
}
#pragma once

typedef int ivec2[2];
#define iv2(x, y) (ivec2){(x), (y)}
#define iv2e {0, 0}

typedef float vec2[2];
#define v2(x, y) (vec2){(x), (y)}
#define v2e {0.0f, 0.0f}

typedef float vec3[3];
#define v3(x, y, z) (vec3){(x), (y), (z)}
#define v3e {0.0f, 0.0f, 0.0f}

typedef float vec4[4];
#define v4(x, y, z, w) (vec4){(x), (y), (z), (w)}
#define v4e {0.0f, 0.0f, 0.0f, 0.0f}

typedef float mat4[16];
#define mat4i { 1.0f, 0.0f, 0.0f, 0.0f, \
				0.0f, 1.0f, 0.0f, 0.0f, \
				0.0f, 0.0f, 1.0f, 0.0,  \
				0.0f, 0.0f, 0.0f, 1.0f}
#define mat4a(M, x, y) M[x * 4 + y]
inline void mat4_ortho(mat4 M, float l, float r, float b, float t, float n, float f)
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

inline void mat4_scale(mat4 M, const vec3 s)
{
	for(int i = 0; i < 3; ++i)
		mat4a(M, i, i) = s[i];
}

inline void mat4_translate(mat4 M, const vec3 s)
{
	for(int i = 0; i < 3; ++i)
		mat4a(M, 3, i) = s[i];
}

//TODO: these scale/translate functions kinda wack, separate set/add ones loool

typedef int fixed;

#define FIXED_POINT 16 /* 16.16 */
#define FIXED_UNIT 1 << FIXED_POINT

#define int2fix(value) ((value) << FIXED_POINT)
#define fix2int(value) ((value) >> FIXED_POINT)

// TODO: Fixed point math (mult/div)
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
void mat4_ortho(mat4 M, float l, float r, float b, float t, float n, float f);
void mat4_scale(mat4 M, const vec3 s);

void mat4_translate(mat4 M, const vec3 s);

void mat4_translate_forward(mat4 M, const vec3 s);

//TODO: these scale/translate functions kinda wack, separate set/add ones loool

typedef int fixed;

#define FIXED_POINT 16 /* 16.16 */
#define SIGN_BIT 31
#define FIXED_UNIT 1 << FIXED_POINT
#define HALF_FIXED_UNIT FIXED_POINT >> 1
#define QUARTER_FIXED_UNIT FIXED_POINT >> 2

#define int2fix(value) ((value) << FIXED_POINT)
#define fix2int(value) ((value) >> FIXED_POINT)

int sign(int x);

// TODO: Fixed point math (mult/div)
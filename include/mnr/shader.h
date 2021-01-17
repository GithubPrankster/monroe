#pragma once

/*
	Calls to `me_shader_create` must at
	some point have `glDeleteProgram` called.
*/

unsigned mr_create_shader(const char* vsrc, const char* fsrc);
void mr_shader_int(const unsigned shr, const char* name, const int var);
void mr_shader_float(const unsigned shr, const char* name, const float var);
void mr_shader_vec2(const unsigned shr, const char* name, const float *var);
void mr_shader_vec3(const unsigned shr, const char* name, const float *var);
void mr_shader_vec4(const unsigned shr, const char* name, const float *var);
void mr_shader_mat4(const unsigned shr, const char* name, const float *var);

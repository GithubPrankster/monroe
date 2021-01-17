#include "mnr/shader.h"
#include "mnr/file.h"
#include <glad/glad.h>
#include <stdio.h>

static void check_err(unsigned prg)
{
	int sc = 0;
	char log[512];
	glGetShaderiv(prg, GL_COMPILE_STATUS, &sc);
	if(!sc){
		glGetShaderInfoLog(prg, 1024, NULL, log);
		printf("[GL]: %s\n", log);
	}
}

unsigned mr_create_shader(const char* vsrc, const char* fsrc)
{
	const char* vert = mr_load_file(vsrc, NULL);
	const char* frag = mr_load_file(fsrc, NULL);

	unsigned vtx = glCreateShader(GL_VERTEX_SHADER);
	unsigned frg = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned prog = glCreateProgram();

	glShaderSource(vtx, 1, &vert, NULL);
	glCompileShader(vtx);
	check_err(vtx);

	glShaderSource(frg, 1, &frag, NULL);
	glCompileShader(frg);
	check_err(frg);	

	glAttachShader(prog, vtx);
	glAttachShader(prog, frg);
	glLinkProgram(prog);
	
	glDeleteShader(frg);
	glDeleteShader(vtx);
	return prog;
}

void mr_shader_int(const unsigned shr, const char* name, const int var)
{
	glUniform1i(glGetUniformLocation(shr, name), var);
}

void mr_shader_float(const unsigned shr, const char* name, const float var)
{
	glUniform1f(glGetUniformLocation(shr, name), var);
}

void mr_shader_vec2(const unsigned shr, const char* name, const float *var)
{
	glUniform2fv(glGetUniformLocation(shr, name), 1, var);
}

void mr_shader_vec3(const unsigned shr, const char* name, const float *var)
{
	glUniform3fv(glGetUniformLocation(shr, name), 1, var);
}

void mr_shader_vec4(const unsigned shr, const char* name, const float *var)
{
	glUniform4fv(glGetUniformLocation(shr, name), 1, var);
}

void mr_shader_mat4(const unsigned shr, const char* name, const float *var)
{
	glUniformMatrix4fv(glGetUniformLocation(shr, name), 1, GL_FALSE, &var[0]);
}


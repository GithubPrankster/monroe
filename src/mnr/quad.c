#include "mnr/quad.h"
#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_VS 8
static vec2 quad[NUM_VS] = {
	v2(1.0f, 1.0f), v2(1.0f, 1.0f),
	v2(1.0f, -1.0f), v2(1.0f, 0.0f),
	v2(-1.0f, -1.0f), v2(0.0f, 0.0f),
	v2(-1.0f, 1.0f), v2(0.0f, 1.0f)
};

#define NUM_IND 6
static const unsigned indies[NUM_IND] = {
	0, 1, 3,
	1, 2, 3
};

mr_quad* mr_create_quad(void)
{
	mr_quad* qd = malloc(sizeof qd);
	if(!qd){
		puts("[MONROE]: Could not allocate quad.");
		return NULL;
	}
	glGenVertexArrays(1, &qd->VAO);
	glGenBuffers(1, &qd->VBO);
	glGenBuffers(1, &qd->EBO);

	glBindVertexArray(qd->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, qd->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * NUM_VS, &quad[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, qd->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * NUM_IND, indies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vec2) * 2, NULL);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vec2) * 2, (void*)(sizeof(vec2)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	return qd;
}

void mr_render_quad(mr_quad* qd)
{
	glBindVertexArray(qd->VAO);
	glDrawElements(GL_TRIANGLES, NUM_IND, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void mr_destroy_quad(mr_quad* qd)
{
	glDeleteBuffers(1, &qd->EBO);
	glDeleteBuffers(1, &qd->VBO);
	glDeleteVertexArrays(1, &qd->VAO);
	free(qd);
}


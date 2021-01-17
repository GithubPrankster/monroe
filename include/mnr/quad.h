#pragma once

#include "vmath.h"

typedef struct{
	unsigned VAO, VBO, EBO;
}mr_quad;

mr_quad* mr_create_quad(void);
void mr_render_quad(mr_quad* qd);
void mr_destroy_quad(mr_quad* qd);

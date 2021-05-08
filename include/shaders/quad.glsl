@ctype mat4 hmm_mat4

@vs vs
in vec2 pos;
in vec2 uv;

uniform vs_params {
    mat4 mvp;
};

out vec2 fuv;

void main() {
    gl_Position = mvp * vec4(pos.x, pos.y, 0.0, 1.0);
    fuv = uv;
}
@end

/* quad fragment shader */
@fs fs
uniform sampler2D tex;

out vec4 frag_color;

in vec2 fuv;

void main() {
    frag_color = texture(tex, fuv);
}
@end

/* quad shader program */
@program quad vs fs
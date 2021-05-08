@ctype mat4 hmm_mat4

@vs vs
in vec2 pos;
in vec2 uv;

out vec2 fuv;

void main() {
    gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);
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
#include <thirdparty/sokol_app.h>
#include <thirdparty/sokol_gfx.h>
#include <tiny_libs.h>
#include <math.h>

#include <shaders/quad.glsl.h>

sg_pass_action pass_action;
sg_pipeline pipeline;
sg_bindings bind;

const float vertices[] = {
    // positions            colors
    -0.5f,  0.5f, 0.5f,     1.0f, 0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, 0.5f,     0.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, 0.5f,     1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f, 1.0f,
};

const uint16_t indices[] = { 0, 1, 2,  0, 2, 3 };

void init(void) {
    sg_setup(&(sg_desc) {
        .context = sapp_sgcontext()
    });

    pass_action = (sg_pass_action){
        .colors[0] = {.action = SG_ACTION_CLEAR, .value = {0.0f, 0.0f, 0.0f, 1.0f} }
    };

    bind.vertex_buffers[0] = sg_make_buffer(&(sg_buffer_desc) {
        .data = SG_RANGE(vertices),
            .label = "quad-verts"
    });

    bind.index_buffer = sg_make_buffer(&(sg_buffer_desc) {
        .type = SG_BUFFERTYPE_INDEXBUFFER,
            .data = SG_RANGE(indices),
            .label = "quad-indices"
    });

    sg_shader quad = sg_make_shader(quad_shader_desc(sg_query_backend()));

    pipeline = sg_make_pipeline(&(sg_pipeline_desc) {
        .shader = quad,
            .index_type = SG_INDEXTYPE_UINT16,
            .layout = {
                .attrs = {
                    [ATTR_vs_position] .format = SG_VERTEXFORMAT_FLOAT3,
                    [ATTR_vs_color0].format = SG_VERTEXFORMAT_FLOAT4
                }
        },
            .label = "quad-pipeline"
    });
}

static void event(const sapp_event* e) {
    if ((e->type == SAPP_EVENTTYPE_KEY_DOWN)) {
        switch (e->key_code) {
        case SAPP_KEYCODE_ESCAPE:
            sapp_request_quit();
            break;
        }
    }
}

void frame(void) {
    sg_begin_default_pass(&pass_action, sapp_width(), sapp_height());
    sg_apply_pipeline(pipeline);
    sg_apply_bindings(&bind);
    sg_draw(0, 6, 1);
    sg_end_pass();
    sg_commit();
}

void cleanup(void) {
    sg_destroy_buffer(bind.index_buffer);
    sg_destroy_buffer(bind.vertex_buffers[0]);
    sg_destroy_pipeline(pipeline);
    sg_shutdown();
}

sapp_desc sokol_main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    return (sapp_desc) {
        .init_cb = init,
            .event_cb = event,
            .frame_cb = frame,
            .cleanup_cb = cleanup,
            .width = 1280,
            .height = 720,
            .window_title = "Ratatan X",
            .icon.sokol_default = true
    };
}
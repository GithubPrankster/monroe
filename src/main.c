#include <thirdparty/sokol_app.h>
#include <thirdparty/sokol_gfx.h>
#include <tiny_libs.h>
#include <math.h>

#include <thirdparty/cute_png.h>
#include <stdlib.h>

#include <thirdparty/HandmadeMath.h>

#include <shaders/quad.glsl.h>

sg_pass_action pass_action;
sg_pipeline pipeline;
sg_bindings bind;
vs_params_t params;

const float vertices[] = {
    // positions            colors
     1.f,  1.f,     1.0f, 1.0f,
     1.f, -1.f,     1.0f, 0.0f,
    -1.f, -1.f,     0.0f, 0.0f,
    -1.f,  1.f,     0.0f, 1.0f
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

    bind.fs_images[SLOT_tex] = sg_alloc_image();

    pipeline = sg_make_pipeline(&(sg_pipeline_desc) {
        .shader = sg_make_shader(quad_shader_desc(sg_query_backend())),
        .index_type = SG_INDEXTYPE_UINT16,
        .layout = {
            .attrs = {
                [ATTR_vs_pos].format = SG_VERTEXFORMAT_FLOAT2,
                [ATTR_vs_uv].format = SG_VERTEXFORMAT_FLOAT2
            }
        },
        .label = "quad-pipeline"
    });

    cp_image_t cosmos = cp_load_png("assets/cosmic.png");
    cp_flip_image_horizontal(&cosmos);

    hmm_mat4 model = HMM_MultiplyMat4(HMM_Scale(HMM_Vec3((float)cosmos.w, (float)cosmos.h, 0.0f)), 
                                      HMM_Translate(HMM_Vec3((float)cosmos.w, (float)cosmos.h, 0.0f)));
    hmm_mat4 proj = HMM_Orthographic(0.0f, 320.f, 180.f, 0.0f, 0.0f, 1.0f);
    params.mvp = HMM_MultiplyMat4(proj, model);

    sg_init_image(bind.fs_images[SLOT_tex], &(sg_image_desc){
        .width = cosmos.w,
        .height = cosmos.h,
        .pixel_format = SG_PIXELFORMAT_RGBA8,
        .min_filter = SG_FILTER_NEAREST,
        .mag_filter = SG_FILTER_NEAREST,
        .data.subimage[0][0] = {
            .ptr = cosmos.pix,
            .size = (size_t)(cosmos.w * cosmos.h * 4),
        }
    });
    free(cosmos.pix);
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
    sg_apply_uniforms(SG_SHADERSTAGE_VS, SLOT_vs_params, &SG_RANGE(params));
    sg_draw(0, 6, 1);
    sg_end_pass();
    sg_commit();
}

void cleanup(void) {
    sg_destroy_image(bind.fs_images[SLOT_tex]);
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
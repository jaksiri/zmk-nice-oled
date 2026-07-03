#include "layer.h"
#include <fonts.h>
#include <zephyr/kernel.h>

void draw_layer_status(lv_obj_t *canvas, const struct status_state *state) {
    char text[10] = {};

#if IS_ENABLED(CONFIG_NICE_EPAPER_ON)
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &pixel_operator_mono_16, LV_TEXT_ALIGN_CENTER);
    if (state->layer_label == NULL) {
        sprintf(text, "Layer %i", state->layer_index);
    } else {
        strncpy(text, state->layer_label, 9);
        to_uppercase(text);
    }
    lv_canvas_draw_text(canvas, CONFIG_NICE_OLED_WIDGET_LAYER_CUSTOM_X,
                        CONFIG_NICE_OLED_WIDGET_LAYER_CUSTOM_Y, 68, &label_dsc, text);
#else
    // OLED: big layer number knocked out of a rounded white badge.
    const int lx = CONFIG_NICE_OLED_WIDGET_LAYER_CUSTOM_X;
    const int ly = CONFIG_NICE_OLED_WIDGET_LAYER_CUSTOM_Y;
    const int size = 24; // square badge

    sprintf(text, "%i", state->layer_index);

    // Rounded white badge background.
    lv_draw_rect_dsc_t badge_dsc;
    init_rect_dsc(&badge_dsc, LVGL_FOREGROUND);
    badge_dsc.radius = 6;
    lv_canvas_draw_rect(canvas, lx, ly, size, size, &badge_dsc);

    // Number in the background color, centered inside the badge.
    lv_draw_label_dsc_t num_dsc;
    init_label_dsc(&num_dsc, LVGL_BACKGROUND, &pixel_operator_mono_22, LV_TEXT_ALIGN_CENTER);
    lv_canvas_draw_text(canvas, lx, ly + 3, size, &num_dsc, text);
#endif // CONFIG_NICE_EPAPER_ON
}

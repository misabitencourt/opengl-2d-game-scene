
int menu_instructions_scene_timeout = 0;

int menu_instructions_scene()
{
    if (++menu_instructions_scene_timeout == 2500) {
        return 0;
    }
    char * text = "Use W S A D";
    char * text_l2 = "To walk";
    void * l1 = get_text_image_line(font_img, text);
    void * l2 = get_text_image_line(font_img, text_l2);
    add_to_scene(
        current_frame, 
        l1, 
        100,
        600, 
        get_str_length(text) * FONT_FRAME_WIDTH,
        font_img.height
    );
    add_to_scene(
        current_frame, 
        l2, 
        200,
        540, 
        get_str_length(text_l2) * FONT_FRAME_WIDTH,
        font_img.height
    );

    return 1;
}
void load_sprites()
{   
    sprite_char = read_png_file("./sprites/char.png");
    sprite_char.frame_width = 32;    
    sprite_char.animation = CHAR_ANIMATION_WALKING_DOWN;
    sprite_char.frame_current = CHAR_ANIMATION_WALKING_DOWN_START;
    sprite_char.frame_start = CHAR_ANIMATION_WALKING_DOWN_START;
    sprite_char.frame_end = CHAR_ANIMATION_WALKING_DOWN_END;
    sprite_char.x = CHAR_INITIAL_POS_X;
    sprite_char.y = CHAR_INITIAL_POS_Y;
    sprite_char.frame_delay = 50;
    sprite_char.frame_delay_current = 1;

    tileset_img = read_png_file("./tilesets/tileset.png");
    tree_img = read_png_file("./sprites/tree.png");
    stone_img = read_png_file("./sprites/stone.png");
    font_img = read_png_file("./sprites/font.png");
    
    bat_img = read_png_file("./sprites/bat.png");    
    bat_img.frame_width = 32;
    bat_img.animation = BAT_ANIMATION_FLYING;
    bat_img.frame_current = BAT_ANIMATION_FLYING_START;
    bat_img.frame_start = BAT_ANIMATION_FLYING_START;
    bat_img.frame_end = BAT_ANIMATION_FLYING_END;
    bat_img.x = 0;
    bat_img.y = 0;
    bat_img.frame_delay = 50;
    bat_img.frame_delay_current = 1;
    bat_img.height = 32;

    for (int i=0; i<BAT_GROUP_SIZE; i++) {
        bat_img_group[i].height = 32;
        bat_img_group[i].frame_width = 32;
        bat_img_group[i].animation = BAT_ANIMATION_FLYING;
        bat_img_group[i].frame_current = BAT_ANIMATION_FLYING_START;
        bat_img_group[i].frame_start = BAT_ANIMATION_FLYING_START;
        bat_img_group[i].frame_end = BAT_ANIMATION_FLYING_END;
        bat_img_group[i].x = 0;
        bat_img_group[i].y = 0;
        bat_img_group[i].frame_delay = 50;
        bat_img_group[i].frame_delay_current = 1;
    }
}
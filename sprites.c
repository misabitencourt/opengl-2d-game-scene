State game_state;
Sprite sprite_char;
Sprite tree_img;
Sprite stone_img;
Sprite tileset_img;
Sprite bat_img;
const int BAT_GROUP_SIZE = 5;
Sprite bat_img_group[5];
Sprite font_img;
void * current_frame;
unsigned int starting = 1;

unsigned int bat_delay = 0;
unsigned int update_bat = 0;

 Sprite read_png_file(char * file_name) 
 {
    Sprite ret;

    int x, y;

    int width, height, number_of_passes;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    char header[8];    // 8 is the maximum size that can be checked

    FILE *fp = fopen(file_name, "rb");
    if (!fp) {
        printf("[read_png_file] File %s could not be opened for reading", file_name);
        exit(0);
    }
            
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)) {
        printf("[read_png_file] File %s is not recognized as a PNG file", file_name);
        exit(0);
    }

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr) {
        printf("[read_png_file] png_create_read_struct failed");
        exit(0);
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        printf("[read_png_file] png_create_info_struct failed");
        exit(0);
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        printf("[read_png_file] Error during init_io");
        exit(0);
    }

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);

    /* read file */
    if (setjmp(png_jmpbuf(png_ptr))) {
        printf("[read_png_file] Error during read_image");
        exit(0);
    }
            
    png_bytep * row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
    unsigned int row_bytes = png_get_rowbytes(png_ptr,info_ptr);
    ret.image = (unsigned char*) malloc(row_bytes * height);

    for (y=0; y<height; y++)
            row_pointers[y] = (png_byte*) malloc(row_bytes);

    png_read_image(png_ptr, row_pointers);

    for (int i = 0; i < height; i++) {        
        memcpy(ret.image+(row_bytes * (height-1-i)), row_pointers[i], row_bytes);
    }

    printf("Asset Loaded: %s \r\n", file_name);

    fclose(fp);

    ret.width = width;
    ret.height = height;
    ret.loaded = 1;
    ret.row_bytes = row_bytes;
 
    return ret;
 }


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

void * get_sprite_frame_image(Sprite sprite)
{   
    unsigned int frame_row_bytes = 4;
    int frame_total_bytes = frame_row_bytes * sprite.frame_width * sprite.height;
    void * ret = malloc(frame_total_bytes);

    for (int i=0; i<sprite.height; i++) {
        void * row_pointer = ret + frame_total_bytes - (frame_row_bytes * (sprite.height-i) * sprite.frame_width);
        void * frame_pointer = sprite.image + // Sprite first pixel pointer
                                  (sprite.frame_width * (sprite.frame_current-1) * frame_row_bytes) + // Jump to frame pixels
                                  (i * sprite.width * frame_row_bytes); // Jump to current line;

        memcpy(row_pointer,
               frame_pointer, 
               sprite.frame_width * frame_row_bytes);
    }

    return ret;
}

void mount_bkg_tileset()
{
    unsigned int frame_row_bytes = 4;
    const int to_paint_bytes = 4 * TILESET_SIZE * TILESET_SIZE;
    void * to_paint = malloc(to_paint_bytes);
    Sprite tileset = tileset_img;
    void * frame_pointer = tileset.image;
    memcpy(to_paint, tileset.image, to_paint_bytes);
    const unsigned int scene_end = frame_row_bytes * SCREEN_WIDTH * SCREEN_HEIGHT;
    if (!starting) {
        free(current_frame);
    }
    current_frame = malloc(scene_end);
    int current_tileset_line = 0;
    int w_bkg_painted = 0;
    int h_bkg_painted = 0;

    // BACKGROUND
    unsigned int padding = 40;
    while (h_bkg_painted <= (SCREEN_HEIGHT - padding)) {
        while (w_bkg_painted <= (SCREEN_WIDTH - padding)) {
            void * dest = current_frame + (h_bkg_painted * SCREEN_WIDTH * frame_row_bytes) + 
                                     (w_bkg_painted * frame_row_bytes);
            void * src = to_paint + (current_tileset_line * TILESET_SIZE * frame_row_bytes);
            memcpy(dest, src, frame_row_bytes * TILESET_SIZE);
            w_bkg_painted += TILESET_SIZE;
        }
        w_bkg_painted = 0;
        h_bkg_painted += 1;
        current_tileset_line = (current_tileset_line >= (TILESET_SIZE-1)) ? 0 : 
                               (current_tileset_line + 1);
    }

    free(to_paint);
}

void add_to_scene(void * scene, void * sprite_frame, int x, int y, int w, int h)
{
    unsigned int frame_row_bytes = 4;
    int printed_lines = 0;

    w = ((x + w) > SCREEN_WIDTH) ? ((w + x) - SCREEN_WIDTH) : w;
    h = ((y + h) > SCREEN_HEIGHT) ? ((y + h) - SCREEN_HEIGHT) : h;

    while (printed_lines != h) {
        void * dest = scene + (y * SCREEN_WIDTH * frame_row_bytes) + 
                              (printed_lines * SCREEN_WIDTH * frame_row_bytes) + 
                              (x * frame_row_bytes);
        void * src = sprite_frame + (frame_row_bytes * printed_lines * w);                
        for (int i=0; i<w; i++) {
            unsigned int * redP = (src+(i*frame_row_bytes));
            unsigned int * greenP = (src+(i*frame_row_bytes)+1);
            unsigned int * blueP = (src+(i*frame_row_bytes)+2);
            uint8_t red = *redP;
            uint8_t blue = *blueP;
            uint8_t green = *greenP;
            if (red == TRANSPARENT_COLOR_RED &&
                green == TRANSPARENT_COLOR_GREEN &&
                blue == TRANSPARENT_COLOR_BLUE) {
                continue;
            }
            memcpy(dest+(i*frame_row_bytes), src+(i*frame_row_bytes), frame_row_bytes);
        }
        printed_lines += 1;
    }
}

int check_char_obstacle_collision()
{
    for (int i=0; i<MAPS_LEVEL_OBSTACLES_LENGTH; i++) {
        int obstacle_w, obstacle_h;
        if (MAPS_LEVEL_OBSTACLES[i][0] == SPRITE_TREE) {
            obstacle_w = tree_img.width;
            obstacle_h = tree_img.height;
        }
        if (MAPS_LEVEL_OBSTACLES[i][0] == SPRITE_STONE) {
            obstacle_w = stone_img.width;
            obstacle_h = stone_img.height;
        }
        if (collision(
            sprite_char.x, 
            MAPS_LEVEL_OBSTACLES[i][1],
            sprite_char.y,
            MAPS_LEVEL_OBSTACLES[i][2],
            sprite_char.frame_width,
            obstacle_w,
            sprite_char.height,
            obstacle_h
        )) {
            return 1;
        }
    }
    return 0;
}

void controls()
{
    if (game_state.up) {
        sprite_char.y += 1;
        if (check_char_obstacle_collision()) {
            sprite_char.y -= 1;
        }
        if (sprite_char.animation != CHAR_ANIMATION_WALKING_UP) {
            sprite_char.frame_current = CHAR_ANIMATION_WALKING_UP_START;
        }
        sprite_char.animation = CHAR_ANIMATION_WALKING_UP;
        sprite_char.frame_start = CHAR_ANIMATION_WALKING_UP_START;
        sprite_char.frame_end = CHAR_ANIMATION_WALKING_UP_END;
    } else if (game_state.down) {
        sprite_char.y -= 1;
        if (check_char_obstacle_collision()) {
            sprite_char.y += 1;
        }
        if (sprite_char.animation != CHAR_ANIMATION_WALKING_DOWN) {
            sprite_char.frame_current = CHAR_ANIMATION_WALKING_DOWN_START;
        }
        sprite_char.animation = CHAR_ANIMATION_WALKING_DOWN;
        sprite_char.frame_start = CHAR_ANIMATION_WALKING_DOWN_START;
        sprite_char.frame_end = CHAR_ANIMATION_WALKING_DOWN_END;
    } else if (game_state.left) {
        sprite_char.x -= 1;
        if (check_char_obstacle_collision()) {
            sprite_char.x += 1;
        }
        if (sprite_char.animation != CHAR_ANIMATION_WALKING_LEFT) {
            sprite_char.frame_current = CHAR_ANIMATION_WALKING_LEFT_START;
        }
        sprite_char.animation = CHAR_ANIMATION_WALKING_LEFT;
        sprite_char.frame_start = CHAR_ANIMATION_WALKING_LEFT_START;
        sprite_char.frame_end = CHAR_ANIMATION_WALKING_LEFT_END;
    } else if (game_state.right) {
        sprite_char.x += 1;
        if (check_char_obstacle_collision()) {
            sprite_char.x -= 1;
        }
        if (sprite_char.animation != CHAR_ANIMATION_WALKING_RIGHT) {
            sprite_char.frame_current = CHAR_ANIMATION_WALKING_RIGHT_START;
        }
        sprite_char.animation = CHAR_ANIMATION_WALKING_RIGHT;
        sprite_char.frame_start = CHAR_ANIMATION_WALKING_RIGHT_START;
        sprite_char.frame_end = CHAR_ANIMATION_WALKING_RIGHT_END;
    }

    sprite_char.x = sprite_char.x < 0 ? 0 : sprite_char.x;
    sprite_char.y = sprite_char.y < 0 ? 0 : sprite_char.y;
    
    sprite_char.x = sprite_char.x > (SCREEN_WIDTH-SCREEN_LIMIT) ? (SCREEN_WIDTH-SCREEN_LIMIT) : sprite_char.x;
    sprite_char.y = sprite_char.y > (SCREEN_HEIGHT-SCREEN_LIMIT) ? (SCREEN_HEIGHT-SCREEN_LIMIT) : sprite_char.y;
}

Sprite update_frame(Sprite sprite)
{
    // Frame update
    sprite.frame_delay_current += 1;
    if (sprite.frame_delay_current > sprite.frame_delay) {
        sprite.frame_current = sprite.frame_current + 1;
        if (sprite.frame_current > sprite.frame_end) {
            sprite.frame_current = sprite.frame_start;
        }
        sprite.frame_delay_current = 0;
    }

    return sprite;
}

void mount_scene()
{    
    int totalsize = SCREEN_HEIGHT * SCREEN_WIDTH * 4;    

    // CREATE BACKGROUND
    mount_bkg_tileset();    
    // Controls
    controls();

    // LIST ACTORS
    sprite_char = update_frame(sprite_char);
    void * sprite_char_frame = get_sprite_frame_image(sprite_char);
    add_to_scene(
        current_frame, 
        sprite_char_frame, 
        sprite_char.x, 
        sprite_char.y, 
        sprite_char.frame_width,
        sprite_char.height
    );
    free(sprite_char_frame);

    // BATS    
    if (bat_delay == 35) {
        update_bat = 1;
        bat_delay = 0;
    } else {
        update_bat = 0;
        bat_delay += 1;
    }
    for (int i=0;i<BAT_GROUP_SIZE; i++) {        
        if (update_bat == 1) {
            bat_img_group[i].frame_current += 1;
            if (bat_img_group[i].frame_current == BAT_ANIMATION_FLYING_END) {
                bat_img_group[i].frame_current = BAT_ANIMATION_FLYING_START;
            }
            if (bat_img_group[i].x == 0) {
                bat_img_group[i].x = 1;
                bat_img_group[i].y = rand() % 600;
            } else if (bat_img_group[i].x > 550) {
                bat_img_group[i].x = 0;
            }
            bat_img_group[i].x += rand() % 15;
        }
        
        bat_img.frame_current = bat_img_group[i].frame_current;
        void * bat_frame = get_sprite_frame_image(bat_img);
        add_to_scene(
            current_frame, 
            bat_frame, 
            bat_img_group[i].x, 
            bat_img_group[i].y, 
            bat_img_group[i].frame_width,
            bat_img_group[i].height
        );
        free(bat_frame);
    }

    // MAP OBSTACLES
    for (int i=0; i<MAPS_LEVEL_OBSTACLES_LENGTH; i++) {
        Sprite current_obstacle;
        int current_obstacle_data_type = MAPS_LEVEL_OBSTACLES[i][0];
        int current_obstacle_data_x = MAPS_LEVEL_OBSTACLES[i][1];
        int current_obstacle_data_y = MAPS_LEVEL_OBSTACLES[i][2];
        if (current_obstacle_data_type == SPRITE_TREE) {
            current_obstacle.width = tree_img.width;
            current_obstacle.height = tree_img.height;
            current_obstacle.frame_width = tree_img.width;
            current_obstacle.frame_current = 1;
            current_obstacle.frame_start = 1;
            current_obstacle.frame_end = 1;
            current_obstacle.frame_delay = 1;
            current_obstacle.image = tree_img.image;
        } else if (current_obstacle_data_type == SPRITE_STONE) {
            current_obstacle.width = stone_img.width;
            current_obstacle.height = stone_img.height;
            current_obstacle.frame_width = stone_img.width;
            current_obstacle.frame_current = 1;
            current_obstacle.frame_start = 1;
            current_obstacle.frame_end = 1;
            current_obstacle.frame_delay = 1;
            current_obstacle.image = stone_img.image;
        }
        current_obstacle.x = current_obstacle_data_x;
        current_obstacle.y = current_obstacle_data_y;
        current_obstacle.loaded = 1;
        void * obstacle_frame = get_sprite_frame_image(current_obstacle);
        add_to_scene(
            current_frame, 
            obstacle_frame, 
            current_obstacle.x, 
            current_obstacle.y, 
            current_obstacle.frame_width,
            current_obstacle.height
        );
        free(obstacle_frame);
    }

    char * text = "0001";
    void * points_text = get_text_image_line(font_img, text);
    if (points_text != NULL) {
        add_to_scene(
            current_frame, 
            points_text, 
            500,
            10, 
            get_str_length(text) * FONT_FRAME_WIDTH,
            font_img.height
        );
    }    

    if (starting) {
        starting = 0;
    }
}
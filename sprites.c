State game_state;
Sprite sprite_char;
Sprite tree_img;
Sprite stone_img;
Sprite tileset_img;
Sprite bat_img;
const int BAT_GROUP_SIZE = 20;
Sprite bat_img_group[20];
Sprite font_img;
void * current_frame;

unsigned int starting = 1;
unsigned int bat_delay = 0;
unsigned int update_bat = 0;
unsigned int current_score = 0;
unsigned int current_score_delay = 0;

int bat_init_delay = 0;

#include "controls.c";
#include "read_png.c";
#include "load_sprites.c";
#include "collision.c";

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

    // BATS
    if (bat_init_delay > 5000) {
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
                    bat_img_group[i].y = rand() % 750;
                } else if (bat_img_group[i].x > 550) {
                    bat_img_group[i].x = 0;
                }
                bat_img_group[i].x += rand() % 25;
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
    } else {
        bat_init_delay += 1;
    }

    // Score
    current_score_delay += 1;
    if (current_score_delay == 600) {
        current_score_delay = 0;
        current_score += 1;
    }    
    char * text = int_to_str_4(current_score);
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
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
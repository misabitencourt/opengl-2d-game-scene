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
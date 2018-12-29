const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

const int TILESET_SIZE = 32;
const int TILESET_BACKGROUND_X = 0;
const int TILESET_BACKGROUND_Y = 0;

const int TILESET_IMG = 0;
const int SPRITE_CHAR = 1;
const int MAX_SPRITES = 100;

const int CHAR_INITIAL_POS_X = 20;
const int CHAR_INITIAL_POS_Y = 45;

const int CHAR_ANIMATION_WALKING_DOWN = 0;
const int CHAR_ANIMATION_WALKING_DOWN_START = 1;
const int CHAR_ANIMATION_WALKING_DOWN_END = 3;

const int CHAR_ANIMATION_WALKING_LEFT = 1;
const int CHAR_ANIMATION_WALKING_LEFT_START = 4;
const int CHAR_ANIMATION_WALKING_LEFT_END = 6;

const int CHAR_ANIMATION_WALKING_RIGHT = 2;
const int CHAR_ANIMATION_WALKING_RIGHT_START = 7;
const int CHAR_ANIMATION_WALKING_RIGHT_END = 9;

const int CHAR_ANIMATION_WALKING_UP = 3;
const int CHAR_ANIMATION_WALKING_UP_START = 10;
const int CHAR_ANIMATION_WALKING_UP_END = 12;

const int TRANSPARENT_COLOR_RED = 255;
const int TRANSPARENT_COLOR_GREEN = 0;
const int TRANSPARENT_COLOR_BLUE = 255;

typedef struct {
    int x;
    int y;
    int loaded;
    int width;
    int height;
    int frame_width;
    int frame_current;
    int frame_start;
    int frame_end;
    int frame_delay;
    int frame_delay_current;
    int animation;
    unsigned int row_bytes;
    GLubyte * image;
    GLuint texture;
} Sprite;

typedef struct {
    int level;
    int img_width;
    int img_height;
    int tile_x;
    int tile_y;
    int tile_width;
    int tile_height;
    GLubyte * image;
} Tileset;

typedef struct {
    int width;
    int height;
    GLubyte * image;
} Scene;

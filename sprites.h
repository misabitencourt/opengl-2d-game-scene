const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 800;
const unsigned int SCREEN_LIMIT = 50;

const unsigned int TILESET_SIZE = 32;
const unsigned int TILESET_BACKGROUND_X = 0;
const unsigned int TILESET_BACKGROUND_Y = 0;

const unsigned int TILESET_IMG = 0;
const unsigned int SPRITE_CHAR = 1;
const unsigned int SPRITE_TREE = 2;
const unsigned int SPRITE_STONE = 3;
const unsigned int SPRITE_FONT = 4;
const unsigned int MAX_SPRITES = 100;

const unsigned int SPRITE_FRAME_WIDTH = 49;
const unsigned int SPRITE_FRAME_HEIGHT = 46;

const unsigned int CHAR_INITIAL_POS_X = 20;
const unsigned int CHAR_INITIAL_POS_Y = 45;

const unsigned int CHAR_ANIMATION_WALKING_DOWN = 0;
const unsigned int CHAR_ANIMATION_WALKING_DOWN_START = 1;
const unsigned int CHAR_ANIMATION_WALKING_DOWN_END = 3;

const unsigned int CHAR_ANIMATION_WALKING_LEFT = 1;
const unsigned int CHAR_ANIMATION_WALKING_LEFT_START = 4;
const unsigned int CHAR_ANIMATION_WALKING_LEFT_END = 6;

const unsigned int CHAR_ANIMATION_WALKING_RIGHT = 2;
const unsigned int CHAR_ANIMATION_WALKING_RIGHT_START = 7;
const unsigned int CHAR_ANIMATION_WALKING_RIGHT_END = 9;

const unsigned int CHAR_ANIMATION_WALKING_UP = 3;
const unsigned int CHAR_ANIMATION_WALKING_UP_START = 10;
const unsigned int CHAR_ANIMATION_WALKING_UP_END = 12;

const unsigned int TRANSPARENT_COLOR_RED = 255;
const unsigned int TRANSPARENT_COLOR_GREEN = 0;
const unsigned int TRANSPARENT_COLOR_BLUE = 255;
const unsigned int INT_BYTES = sizeof(unsigned int);

const unsigned int FONT_FRAME_WIDTH = 48;

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

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


typedef struct {
    int x;
    int y;
    int loaded;
    int width;
    int height;
    int frame_width;
    int frame_current;
    int frame_delay;
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

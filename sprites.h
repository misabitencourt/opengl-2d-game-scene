

typedef struct {
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
    int width;
    int height;
    GLubyte * image;
} Scene;
Sprite sprites[100];
int MAX_SPRITES = 100;
int SPRITE_CHAR = 1;

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
    sprites[SPRITE_CHAR] = read_png_file("./sprites/char.png");
    sprites[SPRITE_CHAR].frame_width = 19;
    sprites[SPRITE_CHAR].frame_current = 2;
    sprites[SPRITE_CHAR].frame_delay = 0;

}

GLubyte * get_frame_image(Sprite sprite)
{
    unsigned int frame_row_bytes = sizeof(png_bytep);
    GLubyte * ret = malloc(frame_row_bytes * sprite.frame_width * sprite.height);

    for (int i = 0; i<sprite.height; i++) {
        GLubyte * row_pointer = ret + (frame_row_bytes * sprite.frame_width * sprite.height) - (frame_row_bytes * (sprite.height-i-1) * sprite.frame_width);
        GLubyte * frame_pointer = sprite.image + // Sprite first pixel pointer
                                  (sprite.width * (sprite.frame_current-1) * 4) + // Jump to frame pixels
                                  ((i-1) * sprite.width * 4); // Jump to current line;

        printf("\r\nCopying to:%i from:%i %i bytes", row_pointer, frame_pointer, sprite.frame_width);
        memcpy(row_pointer,
               frame_pointer, 
               sprite.frame_width*4);
    }

    return ret;
}
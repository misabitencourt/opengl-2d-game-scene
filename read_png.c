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

const char alphabet[79] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,;:?!-#\"'&()[]`/";

unsigned int alphabet_get_char_position(char c)
{
    if (c == '\0') {
        return 999;
    }
    for (int i=0; i<sizeof(alphabet); i++)
    {
        if (alphabet[i] == c)
        {
            return i;
        }
    }

    return 0;
}

void * get_text_image_line(Sprite font, char * text)
{
    unsigned int text_length = 0;    
    int char_count = get_str_length(text);

    unsigned int frame_row_bytes = 4;
    int frame_total_bytes = frame_row_bytes * FONT_FRAME_WIDTH * font.height * char_count;
    int single_char_bytes = frame_row_bytes * FONT_FRAME_WIDTH * font.height;
    if (frame_total_bytes <= 0)
    {
        return NULL;
    }

    void * ret = malloc(frame_total_bytes);
    for (int i=0; i<char_count; i++) 
    {
        char current_char = str_char_at(text, i);
        unsigned int char_index = alphabet_get_char_position(current_char);        
        if ((char_index < 0 || char_index == 999) && (current_char != ' '))
        {
            continue;
        }
        for (int j=0; j<font.height; j++) {
            void * dest = ret + (
                frame_row_bytes * j * FONT_FRAME_WIDTH * char_count
            ) + (
                frame_row_bytes * i * FONT_FRAME_WIDTH
            );
            if (current_char == ' ') {
                for (int k=0; k<FONT_FRAME_WIDTH; k++) {
                    void * pixel_pointer = dest + (k * frame_row_bytes);
                    memcpy(pixel_pointer, &TRANSPARENT_COLOR_RED, 1);
                    memcpy(pixel_pointer+1, &TRANSPARENT_COLOR_GREEN, 1);
                    memcpy(pixel_pointer+2, &TRANSPARENT_COLOR_BLUE, 1);
                }                
                continue;
            }            
            void * src = font.image + (j * font.width * frame_row_bytes) +
                                         (char_index * FONT_FRAME_WIDTH * frame_row_bytes);
            memcpy(dest, src, frame_row_bytes * FONT_FRAME_WIDTH);
        }
    }

    return ret;
}





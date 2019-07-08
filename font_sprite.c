
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

char str_char_at(char * text, unsigned int index)
{
    char * current = malloc(sizeof(char));
    int char_count = 0; 
    do 
    {        
        memcpy(current, text + (char_count * sizeof(char)), sizeof(char));
        if (char_count == index) 
        {
            char result = *current;
            free(current);
            return result;
        }
        char_count++;
    } while(current != '\0');

    return '\0';
}

int get_str_length(char * text)
{
    char current;
    int char_count = 0;
    do 
    {
        char * current_pointer = text + (char_count * sizeof(char));
        current = *current_pointer;
        char_count++;
    } while(current != '\0');

    return char_count-1;
}

GLubyte * get_text_image_line(Sprite font, char * text)
{
    unsigned int text_length = 0;    
    int char_count = get_str_length(text);

    unsigned int frame_row_bytes = sizeof(png_bytep);    
    int frame_total_bytes = frame_row_bytes * FONT_FRAME_WIDTH * font.height * char_count;
    int single_char_bytes = frame_row_bytes * FONT_FRAME_WIDTH * font.height;
    if (frame_total_bytes <= 0)
    {
        return NULL;
    }

    GLubyte * ret = malloc(frame_total_bytes);
    for (int i=0; i<char_count; i++) 
    {
        char current_char = str_char_at(text, i);
        unsigned int char_index = alphabet_get_char_position(current_char);        
        if ((char_index < 1 || char_index == 999) && (current_char != ' '))
        {
            continue;
        }
        for (int j=0; j<font.height; j++) {
            GLubyte * dest = ret + (
                frame_row_bytes * j * FONT_FRAME_WIDTH * char_count
            ) + (
                frame_row_bytes * i * FONT_FRAME_WIDTH
            );
            if (current_char == ' ') {
                for (int k=0; k<FONT_FRAME_WIDTH; k++) {
                    GLubyte * pixel_pointer = dest + (k * frame_row_bytes);
                    memcpy(pixel_pointer, &TRANSPARENT_COLOR_RED, 1);
                    memcpy(pixel_pointer+1, &TRANSPARENT_COLOR_GREEN, 1);
                    memcpy(pixel_pointer+2, &TRANSPARENT_COLOR_BLUE, 1);
                }                
                continue;
            }            
            GLubyte * src = font.image + (j * font.width * frame_row_bytes) +
                                         (char_index * FONT_FRAME_WIDTH * frame_row_bytes);
            memcpy(dest, src, frame_row_bytes * FONT_FRAME_WIDTH);
        }
    }

    return ret;
}





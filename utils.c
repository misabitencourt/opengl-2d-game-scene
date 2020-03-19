
int collision(int x1, int x2, int y1, int y2, int w1, int w2, int h1, int h2)
{
    // printf("\r\nx1: %i, x2: %i, y1: %i, y2: %i, w1: %i, w2: %i, h1: %i, h2: %i",
    //         x1, x2, y1, y2, w1, w2, h1, h2);
    // Horizontal collision
    if (x1 < x2) {
        int limit1 = x1 + w1;
        int limit2 = x2 + w2;
        if (! (limit1 >= x2 && limit1 <= limit2)) {
            return 0;
        }
    } else if (x1 > x2) {
        int limit2 = x2 + w2;
        if (! (x1 <= limit2)) {
            return 0;
        }
    }

    // Vertical collision
    if (y1 < y2) {
        int limit1 = y1 + h1;
        int limit2 = y2 + h2;
        if (! (limit1 >= y2 && limit1 <= limit2)) {
            return 0;
        }
    } else if (y1 > y2) {
        int limit2 = y2 + h2;
        if (! (y1 <= limit2)) {
            return 0;
        }
    }

    return 1;
}

char * num_chars = "0123456789";
char get_num_char(int num)
{
    if (num > 9)
    {
        return 0;
    }
    
    return num_chars[num];
}

char * int_to_str_4(int num)
{    
    if (!num) 
    {
        return "0000";
    }
    
    char * res = malloc(sizeof(char) * 5);
    sprintf(res, "%d", num);
    res[4] = '\0';
    
    return res;
}
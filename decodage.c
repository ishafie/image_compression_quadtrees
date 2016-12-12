#include "includes/quadtree.h"

uint8_t     convert_to_dec(unsigned char *buf, int nb, int len)
{
    char        bin[8];
    int         i;

    i = nb - 8;
    while (i < nb && i < len)
    {
        /*printf("nb = %d et i = %d final = %d\n", nb, i, i - nb + 8);*/
        bin[i - nb + 8] = buf[i];
        printf("%d", buf[i]);
        i++;
    }
    /*i = 0;
    while (i < 8)
    {
        printf("%d\n", bin[i]);
        i++;
    }*/
    return ((uint8_t)strtol(bin, 0, 2));
}

t_color	   start_gen_color(unsigned char *code, int *i, int len)
{
    t_color color;

    color.red = convert_to_dec(code, *i + 8, len);
    printf("][");
    color.green = convert_to_dec(code, *i + 16, len);
    printf("][");
    color.blue = convert_to_dec(code, *i + 24, len);
    printf("][");
    color.alpha = convert_to_dec(code, *i + 32, len);
    *i += 32;
    return (color);
}

void       decode(t_qt **qt, unsigned char *code, int i, int max)
{
    t_color color;

    if (i >= max || !code)
    {
        printf("stop i = %d et max = %d\n", i, max);
        return ;
    }
	if (code[i] == 0)
    {
        printf("0");
        *qt = create_tree();
    }
    else
    {
        printf("1[");
        i++;
        color = start_gen_color(code, &i, max);
        printf("]");
        MLV_convert_rgba_to_color(color.red, color.green, color.blue, color.alpha);
        return ;
    }
    i++;
    decode(&(*qt)->no, code, i, max);
    decode(&(*qt)->ne, code, i, max);
    decode(&(*qt)->se, code, i, max);
    decode(&(*qt)->so, code, i, max);
}

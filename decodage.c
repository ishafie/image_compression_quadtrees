#include "includes/quadtree.h"

uint8_t     convert_to_dec(unsigned char *buf, int nb, int len)
{
    char        bin[8];
    char        *binPtr;
    int         i;
    int         total;

    total = 0;
    i = nb - 8;
    while (i < nb && i < len)
    {
        /*printf("nb = %d et i = %d final = %d\n", nb, i, i - nb + 8);*/
        bin[i - nb + 8] = buf[i];
        printf("%d", buf[i]);
        i++;
    }
    i = 0;
    binPtr = &bin[0];
    while (i < 8)
    {
        total *= 2;
        if (*binPtr++ == 1)
            total += 1;
        i++;
    }
/*    printf("%ld\n", strtol(bin, 0, 2));*/
    return ((uint8_t)total);
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

void       decode(t_qt **qt, unsigned char *code, int *i, int max)
{
    t_color color;

    if (*i >= max || !code)
        return ;
	if (code[*i] == 0)
    {
        printf("0");
        *qt = create_tree();
        *i += 1;
        decode(&(*qt)->no, code, i, max);
        decode(&(*qt)->ne, code, i, max);
        decode(&(*qt)->se, code, i, max);
        decode(&(*qt)->so, code, i, max);
    }
    else
    {
        *qt = create_tree();
        printf("1[");
        *i += 1;
        color = start_gen_color(code, i, max);
        (*qt)->color = MLV_convert_rgba_to_color(color.red, color.green, color.blue, color.alpha);
        return ;
    }

}

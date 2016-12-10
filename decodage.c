#include "includes/quadtree.h"

uint8_t     convert_to_dec(unsigned char *buf, int nb)
{
    char        bin[8];
    int         i;

    i = nb;
    while (buf[i] && i < nb + 8)
    {
        bin[nb - i] = buf[i];
        i++;
    }
    return ((uint8_t)strtol(bin, 0, 2));
}

t_color	   start_gen_color(unsigned char *code, int *i)
{
    t_color color;

    color.red = convert_to_dec(code, *i + 8);
    color.green = convert_to_dec(code, *i + 16);
    color.blue = convert_to_dec(code, *i + 24);
    color.alpha = convert_to_dec(code, *i + 32);
    *i += 40;
    return (color);
}

void       decode(t_qt **qt, unsigned char *code, int i, int max)
{
    t_color color;

    if (i >= max || !code)
        return ;
	if (code[i] == 0)
    {
        *qt = create_tree();
    }
    else
    {
        color = start_gen_color(code, &i);
        MLV_convert_rgba_to_color(color.red, color.green, color.blue, color.alpha);
    }
    i++;
    decode(&(*qt)->no, code, i, max);
    decode(&(*qt)->ne, code, i, max);
    decode(&(*qt)->se, code, i, max);
    decode(&(*qt)->so, code, i, max);
}

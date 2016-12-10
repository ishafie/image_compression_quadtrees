#include "includes/quadtree.h"

void        convert_to_bin(uint8_t c, unsigned char **buf, int *i)
{
    int     index;

    index = 7;
    while (index >= 0)
    {
        (*buf)[*i] = (c | (1u << index)) == c;
        *i += 1;
        index--;
    }
}

int        black_or_white(MLV_Color color)
{
    if (color_equal(MLV_COLOR_WHITE, color, 10))
        return (1);
    return (0);
}

void        convert_to_bin_rgba(MLV_Color color, unsigned char **buf, int *i)
{
    t_color c;

    MLV_Color_to_color(color, &c);
    convert_to_bin(c.red, buf, i);
    convert_to_bin(c.green, buf, i);
    convert_to_bin(c.blue, buf, i);
    convert_to_bin(c.alpha, buf, i);
}

void        encode(t_qt *qt, unsigned char **buf, int *i)
{
    if (!qt)
        return ;
    if (!is_leaf(qt))
    {
        (*buf)[*i] = 0;
        *i = *i + 1;
    }
    else
    {
        (*buf)[*i] = 1;
        *i = *i + 1;
        if (!color_equal(qt->color, MLV_COLOR_WHITE, 10) && !color_equal(qt->color, MLV_COLOR_BLACK, 10))
        {
            convert_to_bin_rgba(qt->color, buf, i);
        }
        else
        {
            (*buf)[*i] = black_or_white(qt->color);
            *i += 1;
        }
    }
    encode(qt->no, buf, i);
    encode(qt->ne, buf, i);
    encode(qt->se, buf, i);
    encode(qt->so, buf, i);
}

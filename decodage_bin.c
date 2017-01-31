#include "includes/quadtree.h"

static uint8_t     convert_to_dec(FILE *fp)
{
    char        bin[8];
    char        *binPtr;
    int         i;
    int         total;

    total = 0;
	i = 0;
    while (i < 8)
    {
		if (fread(&bin[i], 1, 1, fp) == 0)
			return ((uint8_t)total);
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
    return ((uint8_t)total);
}

static t_color	   start_gen_color(FILE *fp)
{
    t_color color;

    color.red = convert_to_dec(fp);
    color.green = convert_to_dec(fp);
    color.blue = convert_to_dec(fp);
    color.alpha = convert_to_dec(fp);
    return (color);
}

void       decode_bin(t_qt **qt, FILE *fp)
{
    t_color color;
	char	c;

    if (feof(fp))
        return ;
	if (fread(&c, 1, 1, fp) == 0)
		return ;
    *qt = create_tree(1);
	if (c == 0)
    {
        decode_bin(&(*qt)->no, fp);
        decode_bin(&(*qt)->ne, fp);
        decode_bin(&(*qt)->se, fp);
        decode_bin(&(*qt)->so, fp);
    }
    else
    {
        color = start_gen_color(fp);
        (*qt)->color = MLV_convert_rgba_to_color(color.red, color.green, color.blue, color.alpha);
        return ;
    }
}

static MLV_Color	gen_black_or_white(FILE *fp)
{
	char	c;

	if (fread(&c, 1, 1, fp) == 0)
		return (MLV_COLOR_BLACK);
	if (c == 0)
		return (MLV_COLOR_BLACK);
	return (MLV_COLOR_WHITE);
}

void       	decode_bin_nocolor(t_qt **qt, FILE *fp)
{
	char	c;

    if (feof(fp))
        return ;
	if (fread(&c, 1, 1, fp) == 0)
		return ;
    *qt = create_tree(1);
	if (c == 0)
    {
        decode_bin_nocolor(&(*qt)->no, fp);
        decode_bin_nocolor(&(*qt)->ne, fp);
        decode_bin_nocolor(&(*qt)->se, fp);
        decode_bin_nocolor(&(*qt)->so, fp);
    }
    else
    {
        (*qt)->color = gen_black_or_white(fp);
        return ;
    }
}

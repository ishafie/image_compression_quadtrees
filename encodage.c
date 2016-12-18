#include "includes/quadtree.h"

void	   write_in_file(const char *name, const unsigned char *buf, int len)
{
    FILE *fp;
    char *filename;
    int     i;
    int     filelen;

    filelen = strlen(name) + 5;
    i = 0;
    filename = (char*)malloc(sizeof(char) * filelen);
    if (!filename)
        malloc_handling();
    while (i < filelen)
    {
        filename[i] = 0;
        i++;
    }
    strcpy(filename, name);
    strcat(filename, ".tgc");
    fp = fopen(name, "wb");
    if (!fp)
        malloc_handling();
    fwrite(buf, sizeof(char), len, fp);
}

void       convert_to_bin(uint8_t c, unsigned char **buf, int *i)
{
    int     index;

    index = 7;
    while (index >= 0)
    {
        (*buf)[*i] = (c | (1u << index)) == c;
        printf("%d", (*buf)[*i]);
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
    printf("][");
    convert_to_bin(c.green, buf, i);
    printf("][");
    convert_to_bin(c.blue, buf, i);
    printf("][");
    convert_to_bin(c.alpha, buf, i);
}

void        encode(t_qt *qt, unsigned char **buf, int *i)
{
    if (!qt)
        return ;
    if (!is_leaf(qt))
    {
        (*buf)[*i] = 0;
        printf("0");
        *i = *i + 1;
    }
    else
    {
        (*buf)[*i] = 1;
        *i = *i + 1;
        printf("1[");
        convert_to_bin_rgba(qt->color, buf, i);
        printf("] i = %d\n", *i);
    }
    encode(qt->no, buf, i);
    encode(qt->ne, buf, i);
    encode(qt->se, buf, i);
    encode(qt->so, buf, i);
}

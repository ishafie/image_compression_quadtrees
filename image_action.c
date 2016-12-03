#include "includes/quadtree.h"

void	MLV_Color_to_color(MLV_Color x, t_color *x_c)
{
	uint8_t x_r, x_g, x_b, x_a;

	MLV_convert_color_to_rgba(x, &x_r, &x_g, &x_b, &x_a);
	(*x_c).red = x_r;
	(*x_c).green = x_g;
	(*x_c).blue = x_b;
	(*x_c).alpha = x_a;
}

void	init_color(t_color *ret)
{
	(*ret).red = 0;
	(*ret).green = 0;
	(*ret).blue = 0;
	(*ret).alpha = 0;
}

int		c_cmp(uint8_t a, uint8_t b, int perte)
{
	if (a == b || (a > b - perte && a < b + perte) || (a < b + perte && a > b - perte))
		return (1);
	return (0);
}

int		color_equal(MLV_Color x, MLV_Color y, int perte)
{
	uint8_t x_r, x_g, x_b, x_a;
	uint8_t y_r, y_g, y_b, y_a;

	MLV_convert_color_to_rgba(x, &x_r, &x_g, &x_b, &x_a);
	MLV_convert_color_to_rgba(y, &y_r, &y_g, &y_b, &y_a);
	if (c_cmp(x_r, y_r, perte) && c_cmp(x_g, y_g, perte) && c_cmp(x_b, y_b, perte) && c_cmp(x_a, y_a, perte))
		return (1);
	return (0);
}

int		color_diff(MLV_Color x, MLV_Color y)
{
	uint8_t x_r, x_g, x_b, x_a;
	uint8_t y_r, y_g, y_b, y_a;

	MLV_convert_color_to_rgba(x, &x_r, &x_g, &x_b, &x_a);
	MLV_convert_color_to_rgba(y, &y_r, &y_g, &y_b, &y_a);
	return (abs(x_r - y_r + x_g - y_g + x_b - y_b + x_a - y_a));
}

void	print_color(MLV_Color x)
{
	uint8_t x_r, x_g, x_b, x_a;

	MLV_convert_color_to_rgba(x, &x_r, &x_g, &x_b, &x_a);
	printf("rgb(%d, %d, %d)\n", x_r, x_g, x_b);
}

void	print_every_color_equal(t_qt **qt, t_qt **tmp, MLV_Color x, int *nb_color)
{
	if (!qt || !(*qt))
		return ;
	if (is_leaf(*qt) && x != (*qt)->color && color_equal(x, (*qt)->color, 6))
	{
		*nb_color -= 1;
		free(*qt);
		*qt = *tmp;
		return ;
	}
	print_every_color_equal(&((*qt)->no), tmp, x, nb_color);
	print_every_color_equal(&((*qt)->ne), tmp, x, nb_color);
	print_every_color_equal(&((*qt)->se), tmp, x, nb_color);
	print_every_color_equal(&((*qt)->so), tmp, x, nb_color);
}

static int		d(int x1, int x2)
{
	return (x2 - ((x2 - x1) / 2));
}

void		draw_quadtree(t_qt *qt, MLV_Image *img, int x1, int x2, int y1, int y2)
{
	if (!qt)
		return ;
	if (is_leaf(qt))
	{
		if (x1 == x2)
			x2++;
		if (y1 == y2)
			y2++;
		MLV_draw_filled_circle(x1 + (x2 - x1)/2, y1 + (y2 - y1)/2, (x2 - x1)/2, qt->color);
		/*MLV_draw_filled_rectangle(x1, y1, x2 - x1, y2 - y1, qt->color);*/
		return ;
	}

	draw_quadtree(qt->no, img, x1, d(x1, x2), y1, d(y1, y2));
	draw_quadtree(qt->ne, img, d(x1, x2), x2, y1, d(y1, y2));
	draw_quadtree(qt->se, img, d(x1, x2), x2, d(y1, y2), y2);
	draw_quadtree(qt->so, img, x1, d(x1, x2), d(y1, y2), y2);

}

MLV_Color	get_average_color_from_image(MLV_Image *img, int x1, int x2, int y1, int y2)
{
	t_color		color;
	t_color		moy;
	int			save_x1;
	int			nb_px;

	nb_px = 0;
	save_x1 = x1;
	init_color(&color);
	init_color(&moy);
	if (x2 < x1 || y2 < y1 || x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0)
		return (MLV_COLOR_BLACK);
	while (y1 < y2)
	{
		while (x1 < x2)
		{
			MLV_get_pixel_on_image(img, x1, y1, &(color.red), &(color.green),
				&(color.blue), &(color.alpha));
			moy.blue += color.blue;
			moy.red += color.red;
			moy.green += color.green;
			moy.alpha += color.alpha;
			x1++;
			nb_px++;
		}
		x1 = save_x1;
		y1++;
	}
	if (nb_px != 0)
	{
		moy.red = moy.red/nb_px;
		moy.green = moy.green/nb_px;
		moy.blue = moy.blue/nb_px;
		moy.alpha = moy.alpha/nb_px;
	}
	else
		MLV_get_pixel_on_image(img, x1, y1, &(moy.red), &(moy.green),
				&(moy.blue), &(moy.alpha));
	return (MLV_convert_rgba_to_color(moy.red, moy.green, moy.blue, moy.alpha));
}

t_color		get_average_rgba_from_image(MLV_Image *img, int x1, int x2, int y1, int y2)
{
	t_color		color;
	t_color		moy;
	int			save_x1;
	int			nb_px;

	nb_px = 0;
	save_x1 = x1;
	init_color(&color);
	init_color(&moy);
	if (x2 < x1 || y2 < y1 || x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0)
		return (moy);
	while (y1 < y2)
	{
		while (x1 < x2)
		{
			MLV_get_pixel_on_image(img, x1, y1, &(color.red), &(color.green),
				&(color.blue), &(color.alpha));
			moy.blue += color.blue;
			moy.red += color.red;
			moy.green += color.green;
			moy.alpha += color.alpha;
			x1++;
			nb_px++;
		}
		x1 = save_x1;
		y1++;
	}
	if (nb_px != 0)
	{
		moy.red = moy.red/nb_px;
		moy.green = moy.green/nb_px;
		moy.blue = moy.blue/nb_px;
		moy.alpha = moy.alpha/nb_px;
	}
	else
		MLV_get_pixel_on_image(img, x1, y1, &(moy.red), &(moy.green),
				&(moy.blue), &(moy.alpha));
	return (moy);
}

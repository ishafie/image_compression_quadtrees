#include "includes/quadtree.h"

void	init_color(t_color *ret)
{	
	(*ret).red = 0;
	(*ret).green = 0;
	(*ret).blue = 0;
	(*ret).alpha = 0;
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

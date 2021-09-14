/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:50:00 by alellouc          #+#    #+#             */
/*   Updated: 2021/09/14 11:50:28 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_draw_square(t_img *img, t_point *start, int size, int color)
{
	int	x;
	int	y;

	y = start->y;
	while (y < size + start->y)
	{
		x = start->x;
		while (x < start->x + size)
			ft_mlx_pixel_put(img, x++, y, color);
		y++;
	}
}

void	ft_draw_object(t_img *img, t_point *object, size_t coef, int color)
{
	while (object)
	{
		object->x *= coef;
		object->y *= coef;
		ft_draw_square(img, object, coef, color);
		object = object->next;
	}
}

/*void	ft_draw_legend_start(t_player *pl, t_img *img, int x, int y)
{
	void	*mlx;
	void	*win;
	int		x_start;
	int		y_start;
	t_point	*point;

	mlx = pl->screen->mlx;
	win = pl->screen->win;
	x_start = img->width / 8;
	y_start = img->height / 8;
	point = ft_init_point(x_start, y_start, 0);
	ft_draw_square(img, point, x_start, turquoise);
	x_start = x + img->width / 3;
	y_start = y + y_start + img->width / 9;
	mlx_string_put(mlx, win, x_start, y_start, turquoise, "Start / Pos");
	ft_point_clear(&point, free);
}

void	ft_draw_legend_exit(t_player *pl, t_img *img, int x, int y)
{
	void	*mlx;
	void	*win;
	int		x_start;
	int		y_start;
	t_point	*point;

	mlx = pl->screen->mlx;
	win = pl->screen->win;
	x_start = img->width / 8;
	y_start = 3 * (img->height / 8);
	point = ft_init_point(x_start, y_start, 0);
	ft_draw_square(img, point, x_start, pink);
	x_start = x + img->width / 3;
	y_start = y + y_start + img->width / 9;
	mlx_string_put(mlx, win, x_start, y_start, pink, "Exit");
	ft_point_clear(&point, free);
}

void	ft_draw_legend_item(t_player *pl, t_img *img, int x, int y)
{
	void	*mlx;
	void	*win;
	int		x_start;
	int		y_start;
	t_point	*point;

	mlx = pl->screen->mlx;
	win = pl->screen->win;
	x_start = img->width / 8;
	y_start = 5 * (img->height / 8);
	point = ft_init_point(x_start, y_start, 0);
	ft_draw_square(img, point, x_start, yellow);
	x_start = x + img->width / 3;
	y_start = y + y_start + img->width / 9;
	mlx_string_put(mlx, win, x_start, y_start, yellow, "Item");
	ft_point_clear(&point, free);
}

void	ft_draw_legend(t_player	*player)
{
	t_img	*img;
	void	*mlx;
	int		x;
	int		y;

	mlx = player->screen->mlx;
	img = ft_create_img(player);
	if (!img)
		return ;
	x = player->screen->width - img->width;
	y = player->screen->height - img->height;
	ft_fill_screen(img, 0xDDFFFFFF);
	ft_draw_legend_start(player, img, x, y);
	ft_draw_legend_exit(player, img, x, y);
	ft_draw_legend_item(player, img, x, y);
	mlx_put_image_to_window(mlx, player->screen->win, img->def, x, y);
	ft_destroy_timg(img, mlx);
}*/

int	ft_draw_map(t_player *player)
{
	int		coef;

	coef = player->coef;
	ft_fill_screen(player->img, ocre);
	ft_draw_object(player->img, player->map->wall, coef, grey);
	ft_draw_object(player->img, player->map->collect, coef, yellow);
	ft_draw_object(player->img, player->map->start, coef, turquoise);
	ft_draw_object(player->img, player->map->end, coef, pink);
	ft_center_image(player, player->pole_pos->x, player->pole_pos->y);
	ft_display_nb_moves(player, 0xFFFFFF);
	ft_draw_minimap(player);
	ft_draw_legend(player);
	return (0);
}

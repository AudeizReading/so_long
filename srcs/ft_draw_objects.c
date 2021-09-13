/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:50:00 by alellouc          #+#    #+#             */
/*   Updated: 2021/09/13 16:34:46 by alellouc         ###   ########.fr       */
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

//void	ft_draw_infos_legend(t_img *img,

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
	ft_draw_square(img, &(t_point){img->width / 8, img->height / 8, 0, NULL}, img->width / 8, turquoise);
	ft_draw_square(img, &(t_point){img->width / 8, 3 * (img->height / 8), 0, NULL}, img->width / 8, pink);
	ft_draw_square(img, &(t_point){img->width / 8, 5 * (img->height / 8), 0, NULL}, img->width / 8, yellow);
	mlx_string_put(mlx, player->screen->win, x + img->width / 3, y + img->height / 8 + img->width / 9, turquoise, "Start / Pos");
	mlx_string_put(mlx, player->screen->win, x + img->width / 3, y + 3 * (img->height / 8) + img->width / 9, pink, "Exit");
	mlx_string_put(mlx, player->screen->win, x + img->width / 3, y + 5 * (img->height / 8) + img->width / 9, yellow, "Item");
	mlx_put_image_to_window(mlx, player->screen->win, img->def, x, y);
	ft_destroy_timg(img, mlx);
}

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

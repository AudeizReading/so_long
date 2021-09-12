/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:50:00 by alellouc          #+#    #+#             */
/*   Updated: 2021/09/12 19:55:32 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_draw_square(t_img *img, t_point *start, int size, int color)
{
	int	x;
	int y;

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

void	ft_draw_minimap(t_player *player)
{
	t_img	*img;
	t_map	*map;
	int		fd;
	void	*mlx;

	mlx = player->screen->mlx;
	img = ft_init_img(player, player->coef / 8);
	fd = open(player->filename, O_RDONLY);
	map = ft_init_map();
	map->first_line = ft_get_map(fd);
	map->lines = ft_map_size(map->first_line);
	map->cols = map->first_line->len;
	ft_get_objects_pos(map);
	img->def = mlx_new_image(player->screen->mlx, img->width, img->height);
	img->addr = mlx_get_data_addr(img->def, &img->bpp, &img->len, &img->end);
	ft_fill_screen(img, 0xDDFFFFFF);
	ft_draw_object(img, map->wall, player->coef / 8, grey_legend);
	ft_draw_object(img, map->collect, player->coef / 8, yellow_legend);
	ft_draw_object(img, map->start, player->coef / 8, turquoise_legend);
	ft_draw_object(img, map->end, player->coef / 8, pink);
	mlx_put_image_to_window(mlx, player->screen->win, img->def, 0, 0);
	ft_destroy_timg(img, mlx);
	ft_clean_map(map);
	close(fd);
}

void	ft_draw_legend(t_player	*player)
{
	t_img	*img;
	void	*mlx;
	int		x;
	int		y;

	img = ft_init_img(player, player->coef / 8);
	mlx = player->screen->mlx;
	x = player->screen->width - img->width;
	y = player->screen->height - img->height;
	img->def = mlx_new_image(mlx, img->width, img->height);
	img->addr = mlx_get_data_addr(img->def, &img->bpp, &img->len, &img->end);
	ft_fill_screen(img, 0xDDFFFFFF);
	printf("x: %d, y: %d\n", x, y);
	ft_draw_square(img, &(t_point){img->width / 8, img->height / 8, 0, NULL}, player->coef / 8, turquoise);
	mlx_string_put(mlx, player->screen->win, x + player->coef, y + img->height / 4, turquoise, "Depart");
	ft_draw_square(img, &(t_point){img->width / 8, img->height - 6 * (img->height / 8), 0, NULL}, player->coef / 8, pink);
	mlx_put_image_to_window(mlx, player->screen->win, img->def, x, y);
	ft_destroy_timg(img, mlx);
}

int		ft_draw_map(t_player *player)
{
	ft_fill_screen(player->img, ocre);
	ft_draw_object(player->img, player->map->wall, player->coef, grey);
	ft_draw_object(player->img, player->map->collect, player->coef, yellow);
	ft_draw_object(player->img, player->map->start, player->coef, turquoise);
	ft_draw_object(player->img, player->map->end, player->coef, pink);
	ft_center_image(player, player->pole_pos->x, player->pole_pos->y);
	ft_draw_minimap(player);
	ft_draw_legend(player);
	return (0);
}

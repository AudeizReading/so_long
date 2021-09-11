/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:50:00 by alellouc          #+#    #+#             */
/*   Updated: 2021/09/11 20:55:51 by alellouc         ###   ########.fr       */
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
	t_img	*legend;
	t_map	*map;
	int		fd;

	legend = ft_init_img(player, player->coef / 8);
	fd = open(player->filename, O_RDONLY);
	map = ft_init_map();
	map->first_line = ft_get_map(fd);
	map->lines = ft_map_size(map->first_line);
	map->cols = map->first_line->len;
	ft_get_objects_pos(map);
	legend->def = mlx_new_image(player->screen->mlx, legend->width, legend->height);
	legend->addr = mlx_get_data_addr(legend->def, &legend->bpp, &legend->len, &legend->end);
	ft_fill_screen(legend, 0xDDFFFFFF);
	ft_draw_object(legend, map->wall, player->coef / 8, grey_legend);
	ft_draw_object(legend, map->collect, player->coef / 8, yellow_legend);
	ft_draw_object(legend, map->start, player->coef / 8, turquoise_legend);
	ft_draw_object(legend, map->end, player->coef / 8, pink);
	mlx_put_image_to_window(player->screen->mlx, player->screen->win, legend->def, 0, 0);
	mlx_destroy_image(player->screen->mlx, legend->def);
	ft_clean_map(map);
	free(legend);
	close(fd);
}

int		ft_draw_map(t_player *player)
{
//	mlx_clear_window(player->screen->mlx, player->screen->win);
	ft_fill_screen(player->img, ocre);
	ft_draw_object(player->img, player->map->wall, player->coef, grey);
	ft_draw_object(player->img, player->map->collect, player->coef, yellow);
	ft_draw_object(player->img, player->map->start, player->coef, turquoise);
	ft_draw_object(player->img, player->map->end, player->coef, pink);
	ft_center_image(player, player->pole_pos->x, player->pole_pos->y);
	ft_draw_minimap(player);
	return (0);
}

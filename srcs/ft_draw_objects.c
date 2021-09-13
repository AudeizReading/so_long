/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:50:00 by alellouc          #+#    #+#             */
/*   Updated: 2021/09/13 14:27:20 by alellouc         ###   ########.fr       */
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

void	ft_draw_map_objects(t_img *img, t_map *map, int coef)
{
	ft_draw_object(img, map->wall, coef, grey_legend);
	ft_draw_object(img, map->collect, coef, yellow_legend);
	ft_draw_object(img, map->start, coef, turquoise_legend);
	ft_draw_object(img, map->end, coef, pink);
}

void	ft_scale_minimap(t_player *player, t_map *map, int *coef)
{
	unsigned int	scr_w;
	unsigned int	scr_h;

	scr_w = player->screen->width;
	scr_h = player->screen->height;
	while (map->cols * (*coef) > scr_w || map->lines * (*coef) > scr_h)
		*coef /= 2;
}

void	ft_draw_minimap(t_player *player)
{
	t_img	*img;
	t_map	*map;
	int		fd;
	void	*mlx;
	int		coef;

	mlx = player->screen->mlx;
	coef = player->coef / 8;
	fd = open(player->filename, O_RDONLY);
	map = ft_init_map();
	map->first_line = ft_get_map(fd);
	map->lines = ft_map_size(map->first_line);
	map->cols = map->first_line->len;
	ft_get_objects_pos(map);
	ft_scale_minimap(player, map, &coef);
	img = ft_init_img(player, coef);
	img->def = mlx_new_image(player->screen->mlx, img->width, img->height);
	img->addr = mlx_get_data_addr(img->def, &img->bpp, &img->len, &img->end);
	ft_fill_screen(img, 0xDDFFFFFF);
	ft_draw_map_objects(img, map, coef);
	mlx_put_image_to_window(mlx, player->screen->win, img->def, 0, 0);
	ft_destroy_timg(img, mlx);
	ft_clean_map(map);
	close(fd);
}

t_img	*ft_create_img(t_player *player)
{
	t_img	*img;
	void	*mlx;

	mlx = player->screen->mlx;
	img = malloc(sizeof(*img));
	if (!img)
		return (NULL);
	img->width = player->screen->width / 6 + player->screen->width / 12;
	img->height = player->screen->height / 6 + player->screen->height / 12;
	img->def = mlx_new_image(mlx, img->width, img->height);
	img->addr = mlx_get_data_addr(img->def, &img->bpp, &img->len, &img->end);
	return (img);
}

//void	ft_draw_infos_legend(t_img *img,

void	ft_draw_legend(t_player	*player)
{
	t_img	*img;
	void	*mlx;
	int		x;
	int		y;

	mlx = player->screen->mlx;
	img =  ft_create_img(player);
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

int		ft_draw_map(t_player *player)
{
	int		coef;

	coef = player->coef;
	ft_fill_screen(player->img, ocre);
	ft_draw_object(player->img, player->map->wall, coef, grey);
	ft_draw_object(player->img, player->map->collect, coef, yellow);
	ft_draw_object(player->img, player->map->start, coef, turquoise);
	ft_draw_object(player->img, player->map->end, coef, pink);
	ft_center_image(player, player->pole_pos->x, player->pole_pos->y);
	ft_draw_minimap(player);
	ft_draw_legend(player);
	return (0);
}

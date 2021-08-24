/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <alellouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 13:05:25 by alellouc          #+#    #+#             */
/*   Updated: 2021/08/24 13:05:36 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_fill_screen(t_img *img, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			ft_mlx_pixel_put(img, x++, y, color);
		}
		y++;
	}
	mlx_put_image_to_window(img->mlx, img->win, img->def, 0, 0);
}

void	ft_draw_screen_grid_map(t_img *img, int color, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			if (x && !(x % (img->width / map->cols))) 
				ft_mlx_pixel_put(img, x++, y, color);
			else if (x && y && !(y % (img->height / map->lines)))
				ft_mlx_pixel_put(img, x++, y, color);
			else
				x++;
		}
		y++;
	}
	mlx_put_image_to_window(img->mlx, img->win, img->def, 0, 0);
}

void	ft_draw_screen_grid_bpp(t_img *img, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			if (x && !(x % img->bpp)) 
				ft_mlx_pixel_put(img, x++, y, color);
			else if (x && y && !(y % img->bpp))
				ft_mlx_pixel_put(img, x++, y, color);
			else
				x++;
		}
		y++;
	}
	mlx_put_image_to_window(img->mlx, img->win, img->def, 0, 0);
}

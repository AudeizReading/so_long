/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <alellouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 13:05:25 by alellouc          #+#    #+#             */
/*   Updated: 2021/09/08 12:53:53 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_fill_screen(t_img *img, int color)
{
	unsigned int	x;
	unsigned int	y;

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
}

void	ft_draw_screen_grid_map(t_img *img, int color, t_map *map)
{
	unsigned int	x;
	unsigned int	y;

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
}

void	ft_draw_screen_grid_bpp(t_img *img, int color)
{
	unsigned int	x;
	unsigned int	y;

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
}

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

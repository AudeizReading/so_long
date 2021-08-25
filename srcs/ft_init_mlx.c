/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <alellouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 12:39:05 by alellouc          #+#    #+#             */
/*   Updated: 2021/08/24 12:39:24 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_get_img_mlx(t_img *img)
{
	img->mlx = mlx_init();
	if (!img->mlx)
		exit(EXIT_FAILURE);
}

void	ft_get_img_win(t_img *img, char *title)
{
	img->win = mlx_new_window(img->mlx, img->width, img->height, title);
	if (!img->win)
		exit(EXIT_FAILURE);
}

void	ft_get_img_def(t_img *img)
{
	img->def = mlx_new_image(img->mlx, img->width, img->height);
	if (!img->def)
		exit(EXIT_FAILURE);
}

void	ft_get_img_addr(t_img *img)
{
	img->addr = mlx_get_data_addr(img->def, &img->bpp, &img->len, &img->end);
	if (!img->addr)
		exit(EXIT_FAILURE);
}

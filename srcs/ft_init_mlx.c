/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <alellouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 12:39:05 by alellouc          #+#    #+#             */
/*   Updated: 2021/08/27 10:57:28 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

//void	ft_get_img_mlx(t_img *img)
void	ft_get_img_mlx(t_screen *screen)
{
//	img->mlx = mlx_init();
	screen->mlx = mlx_init();
//	if (!img->mlx)
	if (screen->mlx)
		exit(EXIT_FAILURE);
}

//void	ft_get_img_win(t_img *img, char *title)
void	ft_get_img_win(t_screen *screen)
{
	//img->win = mlx_new_window(img->mlx, img->width, img->height, title);
	//if (!img->win)
	void			*mlx;
	unsigned int	width;
	unsigned int	height;
	char			*title;

	mlx = screen->mlx;
	width = screen->width;
	height = screen->height;
	title = screen->title;
	screen->win = mlx_new_window(mlx, width, height, title);
	if (!win)
		exit(EXIT_FAILURE);
}

void	ft_get_img_def(t_player *player)
{
	//img->def = mlx_new_image(img->mlx, img->width, img->height);
	//if (!img->def)
	void			*mlx;
	unsigned int	width;
	unsigned int	height;


	mlx = player->screen->mlx;
	width = player->img->width;
	height =  player->img->height;
	player->img->def = mlx_new_image(mlx, width, height);
	if (!player->img->def)
		exit(EXIT_FAILURE);
}

void	ft_get_img_addr(t_img *img)
{
	img->addr = mlx_get_data_addr(img->def, &img->bpp, &img->len, &img->end);
	if (!img->addr)
		exit(EXIT_FAILURE);
}

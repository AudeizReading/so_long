/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_image.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:19:13 by alellouc          #+#    #+#             */
/*   Updated: 2021/09/09 11:19:32 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_center_image(t_player *player, int next_x, int next_y)
{
	int	center_x;
	int	center_y;
	void	*mlx;
	void	*win;
	void	*img;

	center_x = (player->screen->width / 2) - next_x;
	center_y = (player->screen->height / 2) - next_y;
	mlx = player->screen->mlx;
	win = player->screen->win;
	img = player->img->def;
	mlx_put_image_to_window(mlx, win, img, center_x, center_y);
}

t_img	*ft_init_img(t_player *player, size_t coef)
{
	t_img	*img;

	img = malloc(sizeof(*img));
	if (!img)
		return (NULL);
	img->width = player->map->cols * coef;
	img->height = player->map->lines * coef;
	return (img);
}

void	ft_clean_img(t_player *player)
{
	mlx_destroy_image(player->screen->mlx, player->img->def);
	free(player->img);
	player->img = NULL;
}

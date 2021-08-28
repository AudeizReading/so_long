/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook_close_mlx.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <alellouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 14:18:27 by alellouc          #+#    #+#             */
/*   Updated: 2021/08/28 18:19:26 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int		ft_hook_close_mlx(t_player *player)
{
//	mlx_destroy_image(player->screen->mlx, player->img->def);
//	mlx_destroy_window(player->screen->mlx, player->screen->win);
	ft_clean_player(player);
	exit(EXIT_SUCCESS);
	return (0);
}

int		ft_hook_key_esc(int keycode, t_player *player)
{
	if (keycode == 53)
		ft_hook_close_mlx(player);
	return (0);
}

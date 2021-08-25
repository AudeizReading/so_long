/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook_close_mlx.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <alellouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 14:18:27 by alellouc          #+#    #+#             */
/*   Updated: 2021/08/24 14:18:38 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int		ft_hook_close_mlx(t_img *img)
{
	mlx_destroy_image(img->mlx, img->def);
	mlx_destroy_window(img->mlx, img->win);
	exit(EXIT_SUCCESS);
	return (0);
}

int		ft_hook_key_esc(int keycode, t_img *img)
{
	if (keycode == 53)
		ft_hook_close_mlx(img);
	return (0);
}

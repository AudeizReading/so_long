/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_stats.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 09:38:02 by alellouc          #+#    #+#             */
/*   Updated: 2021/09/10 08:29:40 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_print_moves_stats(int keycode, t_player *player)
{
	int total_moves;

	total_moves = player->pole_pos->pos;
	ft_putstr("Move to ");
	if (!keycode)
		ft_putstr("left");
	else if (keycode == 1)
		ft_putstr("down");
	else if (keycode == 2)
		ft_putstr("right");
	else if (keycode == 13)
		ft_putstr("up");
	ft_putstr(".\nYou have made ");
	ft_putnbr(total_moves);
	ft_putendl(" moves since the beginning of the game.");
}

void	ft_print_final_stats(t_player *player)
{
	int	nb_items;
	int	total_items;
	int	total_moves;

	nb_items = player->nb_collect;
	total_items = ft_point_list_size(player->map->collect);
	total_moves = player->pole_pos->pos;
	ft_putstr("\nGame is over now. You have collected ");
	ft_putnbr(nb_items);
	ft_putstr(" / ");
	ft_putnbr(total_items);
	ft_putstr(" items. You have made ");
	ft_putnbr(total_moves);
	ft_putendl(" moves.");
	ft_putendl("You win this game.");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:17:34 by alellouc          #+#    #+#             */
/*   Updated: 2021/09/08 22:53:06 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"             

t_player	*ft_init_player(char **file, size_t w, size_t h, char *title)
{
	t_player	*player;
	int			start_x;
	int			start_y;

	player = malloc(sizeof(*player));
	if (!player)
		return (NULL);
	player->nb_collect = 0;
	player->fd = ft_open_map(file[1]);
	if (!player->fd)
		return NULL;
	player->map = ft_parse_map(player->fd, file);
	if (!player->map)
		return NULL;
	player->coef = 64;
	start_x = player->map->start->x * player->coef;
	start_y = player->map->start->y * player->coef;
	player->pole_pos = ft_init_point(start_x, start_y, 0);
	if (!player->pole_pos)
		return (NULL);
	player->screen = ft_init_screen(title, w, h);
	if (!player->screen)
		return (NULL);
	player->img = ft_init_img(player, player->coef);
	if (!player->img)
		return NULL;
	ft_get_img_def(player);
	ft_get_img_addr(player->img);
	return (player);
}

void	ft_clean_player(t_player *player)
{
	ft_clean_map(player->map);
	ft_point_clear(&player->pole_pos, free);
	ft_clean_img(player);
	ft_clean_screen(player->screen);
	free(player);
	close(player->fd);
}

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
	if (nb_items < total_items)
		ft_putendl("You have failed your mission to collecting ALL the items.");
	else
		ft_putendl("You win this game.");
}

void	ft_change_player_pos(t_player *player, int next_x, int next_y, int key)
{
	t_point	*tmp;
	size_t	pos;

	pos = player->pole_pos->pos;
	ft_draw_square(player->img, player->pole_pos, player->coef, ocre);
	tmp = ft_init_point(next_x, next_y, pos + 1);
	ft_point_addback(&player->pole_pos, tmp);
	player->pole_pos = player->pole_pos->next;
	ft_draw_square(player->img, player->pole_pos, player->coef, turquoise);
	ft_print_moves_stats(key, player);
	mlx_clear_window(player->screen->mlx, player->screen->win);
	ft_center_image(player, next_x, next_y);
}
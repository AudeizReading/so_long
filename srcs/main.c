#include "../includes/so_long.h"

void	ft_handle_exit(t_player *player, int x, int y, int keycode)
{
	int	nb_items;
	int	total_items;

	nb_items = player->nb_collect;
	total_items = ft_point_list_size(player->map->collect);
	if (ft_is_pixel_color(player, x, y, pink) && nb_items == total_items)
	{
		ft_change_player_pos(player, x, y, keycode);
		ft_print_final_stats(player);
		ft_hook_close_mlx(player);
	}
	else if (ft_is_pixel_color(player, x, y, pink) && nb_items != total_items)
	{
		ft_putstr("\nYou only have collected ");
		ft_putnbr(nb_items);
		ft_putstr(" / ");
		ft_putnbr(total_items);
		ft_putendl(" items. You cannot exit until all items are collected.");
	}
}

void	ft_handle_items(t_player *player, int x, int y)
{
	if (ft_is_pixel_color(player, x, y, yellow))
		player->nb_collect++;
}

int		ft_hook_key_s(int keycode, t_player *player)
{
	int	next_x;
	int	next_y;

	next_x = player->pole_pos->x;
	next_y = player->pole_pos->y + player->coef;
	if (keycode == 1 && player->pole_pos->y < (int)player->img->height - player->coef * 2)
	{
		if (!ft_is_pixel_color(player, next_x, next_y, grey))
		{
			ft_handle_exit(player, next_x, next_y, keycode);
			ft_handle_items(player, next_x, next_y);
			if (!ft_is_pixel_color(player, next_x, next_y, pink))
			{
				ft_change_player_pos(player, next_x, next_y, keycode);
				mlx_string_put(player->screen->mlx, player->screen->win, player->pole_pos->x, player->pole_pos->y, 0, "P");
			}
		}
	}
	return (0);
}

int		ft_hook_key_w(int keycode, t_player *player)
{
	int	next_y;
	int	next_x;

	next_y = player->pole_pos->y - player->coef;
	next_x = player->pole_pos->x;
	if (keycode == 13 && player->pole_pos->y > player->coef)
	{
		if (!ft_is_pixel_color(player, next_x, next_y, grey))
		{
			ft_handle_exit(player, next_x, next_y, keycode);
			ft_handle_items(player, next_x, next_y);
			if (!ft_is_pixel_color(player, next_x, next_y, pink))
			{
				ft_change_player_pos(player, next_x, next_y, keycode);
				mlx_string_put(player->screen->mlx, player->screen->win, player->pole_pos->x, player->pole_pos->y, 0, "P");
			}
		}
	}
	return (0);
}

int		ft_hook_key_a(int keycode, t_player *player)
{
	int	next_x;
	int	next_y;

	next_x = player->pole_pos->x - player->coef;
	next_y = player->pole_pos->y;
	if (keycode == 0 && player->pole_pos->x > player->coef)
	{
		if (!ft_is_pixel_color(player, next_x, next_y, grey))
		{
			ft_handle_exit(player, next_x, next_y, keycode);
			ft_handle_items(player, next_x, next_y);
			if (!ft_is_pixel_color(player, next_x, next_y, pink))
			{
				ft_change_player_pos(player, next_x, next_y, keycode);
				mlx_string_put(player->screen->mlx, player->screen->win, player->pole_pos->x, player->pole_pos->y, 0, "P");
			}
		}
	}
	return (0);
}

int		ft_hook_key_d(int keycode, t_player *player)
{
	int	next_x;
	int	next_y;

	next_x = player->pole_pos->x + player->coef;
	next_y = player->pole_pos->y;
	if (keycode == 2 && player->pole_pos->x < (int)player->img->width - player->coef * 2)
	{
		if (!ft_is_pixel_color(player, next_x, next_y, grey))
		{
			ft_handle_exit(player, next_x, next_y, keycode);
			ft_handle_items(player, next_x, next_y);
			if (!ft_is_pixel_color(player, next_x, next_y, pink))
			{
				ft_change_player_pos(player, next_x, next_y, keycode);
				mlx_string_put(player->screen->mlx, player->screen->win, player->pole_pos->x, player->pole_pos->y, 0, "P");
			}
		}
	}
	return (0);
}

int		key_hook(int keycode, t_player *player)
{
	ft_hook_key_esc(keycode, player);
	ft_hook_key_a(keycode, player);
	ft_hook_key_s(keycode, player);
	ft_hook_key_d(keycode, player);
	ft_hook_key_w(keycode, player);
	return (0);
}

int	main(int argc, char **argv)
{
	t_player	*player;

	if (argc == 2)
	{
		player = ft_init_player(argv, 768, 576, "so_long, and thanks for all the fishes");
		if (!player)
			exit(EXIT_FAILURE);
		ft_draw_map(player);
		mlx_hook(player->screen->win, 17, 1L << 2, ft_hook_close_mlx, player);
		mlx_hook(player->screen->win, 2, 1L << 0, key_hook, player);
		mlx_loop(player->screen->mlx);
		mlx_loop_hook(player->screen->mlx, ft_draw_map, player);
		ft_clean_player(player);
	}
	else
		ft_parse_map_error(22);
	return (0);
}

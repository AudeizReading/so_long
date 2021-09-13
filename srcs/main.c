#include "../includes/so_long.h"

void	ft_display_nb_moves(t_player *player, int color)
{
	int		x;
	int		y;
	char	*moves;
	void	*mlx;
	void	*win;

	mlx = player->screen->mlx;
	win = player->screen->win;
	moves = ft_itoa(player->pole_pos->pos);
	x = player->screen->width - player->coef;
	if (ft_strlen(moves) < 3)
		x += player->coef / 2;
	y = player->coef / 2;
	mlx_string_put(mlx, win, x, y, color, moves);
	free(moves);
}

/*void	ft_handle_exit(t_player *player, int x, int y, int keycode)
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
}*/

int	main(int argc, char **argv)
{
	t_player	*player;

	if (argc == 2)
	{
		player = ft_init_player(argv, 768, 576, "so_long, and thanks for all the fishes");
		if (!player)
			exit(EXIT_FAILURE);
		ft_draw_map(player);
		ft_display_nb_moves(player, 0xFFFFFF);
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

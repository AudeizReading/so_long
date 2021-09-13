#include "../includes/so_long.h"

/*void	ft_display_nb_moves(t_player *player, int color)
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
}*/

int	main(int argc, char **argv)
{
	t_player	*player;
	char		*title;

	title = ft_strdup("SO_LONG - and thanks for all the fishes");
	if (!title)
		exit(EXIT_FAILURE);
	if (argc == 2)
	{
		player = ft_init_player(argv, 768, 576, title);
		if (!player)
			exit(EXIT_FAILURE);
		ft_draw_map(player);
		mlx_hook(player->screen->win, 17, 1L << 2, ft_hook_close_mlx, player);
		mlx_hook(player->screen->win, 2, 1L << 0, key_hook, player);
		mlx_loop(player->screen->mlx);
		ft_clean_player(player);
	}
	else
		ft_parse_map_error(22);
	free(title);
	return (0);
}

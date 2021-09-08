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
			if (ft_is_pixel_color(player, next_x, next_y, pink))
			{
				ft_change_player_pos(player, next_x, next_y, keycode);
				ft_print_final_stats(player);
				ft_hook_close_mlx(player);
			}
			if (ft_is_pixel_color(player, next_x, next_y, yellow))
				player->nb_collect++;
			ft_change_player_pos(player, next_x, next_y, keycode);
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
			if (ft_is_pixel_color(player, next_x, next_y, pink))
			{
				ft_change_player_pos(player, next_x, next_y, keycode);
				ft_print_final_stats(player);
				ft_hook_close_mlx(player);
			}
			if (ft_is_pixel_color(player, next_x, next_y, yellow))
				player->nb_collect++;
			ft_change_player_pos(player, next_x, next_y, keycode);
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
			if (ft_is_pixel_color(player, next_x, next_y, pink))
			{
				ft_change_player_pos(player, next_x, next_y, keycode);
				ft_print_final_stats(player);
				ft_hook_close_mlx(player);
			}
			if (ft_is_pixel_color(player, next_x, next_y, yellow))
				player->nb_collect++;
			ft_change_player_pos(player, next_x, next_y, keycode);
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
			if (ft_is_pixel_color(player, next_x, next_y, pink))
			{
				ft_change_player_pos(player, next_x, next_y, keycode);
				ft_print_final_stats(player);
				ft_hook_close_mlx(player);
			}
			if (ft_is_pixel_color(player, next_x, next_y, yellow))
				player->nb_collect++;
			ft_change_player_pos(player, next_x, next_y, keycode);
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

void	ft_draw_object(t_img *img, t_point *object, size_t coef, int color)
{
	while (object)
	{
		object->x *= coef;
		object->y *= coef;
		ft_draw_square(img, object, coef, color);
		object = object->next;
	}
}

int	ft_draw_map(t_player *player)
{
	mlx_clear_window(player->screen->mlx, player->screen->win);
	ft_fill_screen(player->img, ocre);
	ft_draw_object(player->img, player->map->wall, player->coef, grey);
	ft_draw_object(player->img, player->map->collect, player->coef, yellow);
	ft_draw_object(player->img, player->map->start, player->coef, turquoise);
	ft_draw_object(player->img, player->map->end, player->coef, pink);
	ft_center_image(player, player->pole_pos->x, player->pole_pos->y);
	return (0);
}

int	ft_open_map(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_parse_map_error(errno);
	return (fd);
}

t_screen	*ft_init_screen(char *title, size_t width, size_t height)
{
	t_screen	*screen;

	screen = malloc(sizeof(*screen));
	screen->title = ft_strdup(title);
	screen->width = width;
	screen->height = height;
	ft_get_img_mlx(screen);
	ft_get_img_win(screen);
	return (screen);
}

void	ft_clean_screen(t_screen *screen)
{
	free(screen->title);
	mlx_destroy_window(screen->mlx, screen->win);
	free(screen);
	screen = NULL;
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

int	main(int argc, char **argv)
{
	t_player	*player;

	if (argc == 2)
	{
		player = ft_init_player(argv, 768, 576, "so_long, and thanks for all the fishes");
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

#include "../includes/so_long.h"

void	ft_draw_square(t_img *img, t_point *start, int size, int color)
{
	int	x;
	int y;

	y = start->y;
	while (y < size + start->y)
	{
		x = start->x;
		while (x < start->x + size)
			ft_mlx_pixel_put(img, x++, y, color);
		y++;
	}
}

t_bool	ft_is_pixel_color(t_player *player, int x, int y, int color)
{
	int		offset;

	offset = (y * player->img->len + x * (player->img->bpp / 8));
	if (*(int *)(player->img->addr + offset) == color)
			return (e_true);
	return (e_false);
}

void	ft_print_final_stats(t_player *player)
{
	int	nb_items;
	int	total_items;
	int	total_moves;

	nb_items = player->nb_collect;
	total_items = ft_point_list_size(player->map->collect);
	total_moves = player->pole_pos->pos;
	ft_putstr("Hello de Lu\n");
}

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

void	ft_change_player_pos(t_player *player, int next_x, int next_y)
{
	t_point	*tmp;
	size_t	pos;

	pos = player->pole_pos->pos;
	ft_draw_square(player->img, player->pole_pos, player->coef, ocre);
	tmp = ft_init_point(next_x, next_y, pos + 1);
	ft_point_addback(&player->pole_pos, tmp);
	player->pole_pos = player->pole_pos->next;
	ft_draw_square(player->img, player->pole_pos, player->coef, turquoise);
	// Have to delete printf and change the message
	printf("Move to left. You have made %d move since the beginning of the game\n", player->pole_pos->pos);
	mlx_clear_window(player->screen->mlx, player->screen->win);
	ft_center_image(player, next_x, next_y);
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
				ft_change_player_pos(player, next_x, next_y);
				ft_print_final_stats(player);
				printf("Le jeu est fini.\nVous avez récolté %d / %d items.\nVous avez fait %d déplacements\n", player->nb_collect, ft_point_list_size(player->map->collect), player->pole_pos->pos);
				ft_hook_close_mlx(player);
			}
			if (ft_is_pixel_color(player, next_x, next_y, yellow))
				player->nb_collect++;
			ft_change_player_pos(player, next_x, next_y);
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
				ft_change_player_pos(player, next_x, next_y);
				ft_print_final_stats(player);
				printf("Le jeu est fini.\nVous avez récolté %d / %d items.\nVous avez fait %d déplacements\n", player->nb_collect, ft_point_list_size(player->map->collect), player->pole_pos->pos);
				ft_hook_close_mlx(player);
			}
			if (ft_is_pixel_color(player, next_x, next_y, yellow))
				player->nb_collect++;
			ft_change_player_pos(player, next_x, next_y);
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
				ft_change_player_pos(player, next_x, next_y);
				ft_print_final_stats(player);
				printf("Le jeu est fini.\nVous avez récolté %d / %d items.\nVous avez fait %d déplacements\n", player->nb_collect, ft_point_list_size(player->map->collect), player->pole_pos->pos);
				ft_hook_close_mlx(player);
			}
			if (ft_is_pixel_color(player, next_x, next_y, yellow))
				player->nb_collect++;
			ft_change_player_pos(player, next_x, next_y);
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
				ft_change_player_pos(player, next_x, next_y);
				ft_print_final_stats(player);
				printf("Le jeu est fini.\nVous avez récolté %d / %d items.\nVous avez fait %d déplacements\n", player->nb_collect, ft_point_list_size(player->map->collect), player->pole_pos->pos);
				ft_hook_close_mlx(player);
			}
			if (ft_is_pixel_color(player, next_x, next_y, yellow))
				player->nb_collect++;
			ft_change_player_pos(player, next_x, next_y);
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
	mlx_put_image_to_window(player->screen->mlx, player->screen->win, player->img->def, (player->screen->width / 2) - player->pole_pos->x, (player->screen->height / 2) - player->pole_pos->y);
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

t_player	*ft_init_player(char **file, size_t scr_width, size_t scr_height, char *title)
{
	t_player	*player;

	player = malloc(sizeof(*player));
	player->fd = ft_open_map(file[1]);
	player->coef = 64;
	player->nb_collect = 0;
	player->map = ft_parse_map(player->fd, file);
	player->pole_pos = ft_init_point(player->map->start->x * player->coef, player->map->start->y * player->coef, 0);
	player->screen = ft_init_screen(title, scr_width, scr_height);
	player->img = ft_init_img(player, player->coef);
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

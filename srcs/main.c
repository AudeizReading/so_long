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

int		ft_hook_key_s(int keycode, t_player *player)
{
/*	if (keycode == 1 && img->coord->y < img->height - 64 * 2)
	{
		ft_draw_square(img, img->coord, 64, 0x993366);
		img->coord->y += img->bpp * 2;
		img->coord->pos++;
		ft_draw_square(img, img->coord, 64, 0x00AAAA);
		mlx_put_image_to_window(img->mlx, img->win, img->def, img->coord->x, img->coord->y);
		printf("During hook s: img->coord->y %d, img->coord->x %d img->coord->pos %d\n", img->coord->y, img->coord->x, img->coord->pos);
	}*/
	int	coef = 64;
	size_t	pos = player->pole_pos->pos;
	if (keycode == 1 && player->pole_pos->y < (int)player->img->height - coef * 2)
	{
		// C'est censé recouvrir le précédent carré - voir si nécessaire
		ft_draw_square(player->img, player->pole_pos, coef, 0x993366);
		// c'est ici qu'il faut faire player->pole_pos = player->pole_pos->next et init le point tmp
		// Il faudra aussi checker si la nouvelle case est libre d'acces
		player->pole_pos->y += coef;
		pos++;
		player->pole_pos->pos = pos;
		ft_draw_square(player->img, player->pole_pos, coef, 0x00AAAA);
		mlx_put_image_to_window(player->screen->mlx, player->screen->win, player->img->def, player->pole_pos->x, player->pole_pos->y);
		printf("During hook s: player->pole_pos->y %d, player->pole_pos->x %d player->pole_pos->pos %d\n", player->pole_pos->y, player->pole_pos->x, player->pole_pos->pos);
	}
	return (0);
}

// Attention a modif img->bpp * 2 et 64
//int		ft_hook_key_w(int keycode, t_img *img)
int		ft_hook_key_w(int keycode, t_player *player)
{
/*	if (keycode == 13 && img->coord->y > 64)
	{
		ft_draw_square(img, img->coord, 64, 0x993366);
		img->coord->y -= img->bpp * 2;
		img->coord->pos++;
		ft_draw_square(img, img->coord, 64, 0x00AAAA);
		mlx_put_image_to_window(img->mlx, img->win, img->def, img->coord->x, img->coord->y);
		printf("During hook w: img->coord->y %d, img->coord->x %d img->coord->pos %d\n", img->coord->y, img->coord->x, img->coord->pos);
	}*/
	int	coef = 64;
	size_t	pos = player->pole_pos->pos;
	if (keycode == 13 && player->pole_pos->y > coef)
	{
		// C'est censé recouvrir le précédent carré - voir si nécessaire
		ft_draw_square(player->img, player->pole_pos, coef, 0x993366);
		// c'est ici qu'il faut faire player->pole_pos = player->pole_pos->next et init le point tmp
		// Il faudra aussi checker si la nouvelle case est libre d'acces
		player->pole_pos->y -= coef * 2;
		pos++;
		player->pole_pos->pos = pos;
		ft_draw_square(player->img, player->pole_pos, coef, 0x00AAAA);
	// Keep in mind that coordonates are important! Don't mess with it !
		mlx_put_image_to_window(player->screen->mlx, player->screen->win, player->img->def, player->pole_pos->x, player->pole_pos->y);
		printf("During hook w: player->pole_pos->y %d, player->pole_pos->x %d player->pole_pos->pos %d\n", player->pole_pos->y, player->pole_pos->x, player->pole_pos->pos);
	}
	return (0);
}

// Attention a modif img->bpp * 2 et 64
//int		ft_hook_key_a(int keycode, t_img *img)
int		ft_hook_key_a(int keycode, t_player *player)
{
/*	if (keycode == 0 && img->coord->x > 64)
	{
		ft_draw_square(img, img->coord, 64, 0x993366);
		img->coord->x -= img->bpp * 2;
		img->coord->pos++;
		ft_draw_square(img, img->coord, 64, 0x00AAAA);
	// Keep in mind that coordonates are important! Don't mess with it !
		mlx_put_image_to_window(img->mlx, img->win, img->def, img->coord->x, img->coord->y);
		printf("During hook a: img->coord->y %d, img->coord->x %d img->coord->pos %d\n", img->coord->y, img->coord->x, img->coord->pos);
	}*/
	int	coef = 64;
	size_t	pos = player->pole_pos->pos;
	if (keycode == 0 && player->pole_pos->x > coef)
	{
		// C'est censé recouvrir le précédent carré - voir si nécessaire
		ft_draw_square(player->img, player->pole_pos, coef, 0x993366);
		// c'est ici qu'il faut faire player->pole_pos = player->pole_pos->next et init le point tmp
		// Il faudra aussi checker si la nouvelle case est libre d'acces
		player->pole_pos->x -= coef * 2;
		pos++;
		player->pole_pos->pos = pos;
		ft_draw_square(player->img, player->pole_pos, coef, 0x00AAAA);
	// Keep in mind that coordonates are important! Don't mess with it !
		mlx_put_image_to_window(player->screen->mlx, player->screen->win, player->img->def, player->pole_pos->x, player->pole_pos->y);
		printf("During hook a: player->pole_pos->y %d, player->pole_pos->x %d player->pole_pos->pos %d\n", player->pole_pos->y, player->pole_pos->x, player->pole_pos->pos);
	}
	return (0);
}

// Attention a modif img->bpp * 2 et 64
//int		ft_hook_key_d(int keycode, t_img *img)
int		ft_hook_key_d(int keycode, t_player *player)
{
/*	if (keycode == 2 && img->coord->x < img->width - 64 * 2)
	{
		ft_draw_square(img, img->coord, 64, 0x993366);
		img->coord->x += img->bpp * 2;
		img->coord->pos++;
		ft_draw_square(img, img->coord, 64, 0x00AAAA);
	// Keep in mind that coordonates are important! Don't mess with it !
		mlx_put_image_to_window(img->mlx, img->win, img->def, img->coord->x, img->coord->y);
		printf("During hook d: img->coord->y %d, img->coord->x %d img->coord->pos %d\n", img->coord->y, img->coord->x, img->coord->pos);
	}*/
	int	coef = 64;
	size_t	pos = player->pole_pos->pos;
	if (keycode == 2 && player->pole_pos->x < (int)player->img->width - coef * 2)
	{
		// C'est censé recouvrir le précédent carré - voir si nécessaire
		ft_draw_square(player->img, player->pole_pos, coef, 0x993366);
		// c'est ici qu'il faut faire player->pole_pos = player->pole_pos->next et init le point tmp
		// Il faudra aussi checker si la nouvelle case est libre d'acces
		player->pole_pos->x += coef * 2;
		pos++;
		player->pole_pos->pos = pos;
		ft_draw_square(player->img, player->pole_pos, coef, 0x00AAAA);
	// Keep in mind that coordonates are important! Don't mess with it !
		mlx_put_image_to_window(player->screen->mlx, player->screen->win, player->img->def, player->pole_pos->x, player->pole_pos->y);
		printf("During hook d: player->pole_pos->y %d, player->pole_pos->x %d player->pole_pos->pos %d\n", player->pole_pos->y, player->pole_pos->x, player->pole_pos->pos);
	}
	return (0);
}

int		key_hook(int keycode, t_player *player)
{
	ft_hook_key_esc(keycode, player);
//	ft_hook_key_a(keycode, player);
	ft_hook_key_s(keycode, player);
//	ft_hook_key_d(keycode, player);
//	ft_hook_key_w(keycode, player);
	return (0);
}

int	ft_display_screen(t_player *player)
{
	int color;

	color = 0x993366;
	ft_fill_screen(player->img, color);
	//ft_draw_square(img, img->coord, 64, 0x00BBBB);
	// Keep in mind that coordonates are important! Don't mess with it !
	mlx_put_image_to_window(player->screen->mlx, player->screen->win, player->img->def, 0, 0);
	return (1);
}

void	ft_draw_wall(t_player *player)
{
	size_t	coef = 64;
	ft_fill_screen(player->img, 0x993366);
	while (player->map->wall)
	{
		player->map->wall->x *= coef;
		player->map->wall->y *= coef;
		ft_draw_square(player->img, player->map->wall, coef, 0x555555);
		printf("player->map->wall->x %d, player->map->wall->y %d\n", player->map->wall->x, player->map->wall->y);
		player->map->wall = player->map->wall->next;
	}
	while (player->map->collect)
	{
		player->map->collect->x *= coef;
		player->map->collect->y *= coef;
		ft_draw_square(player->img, player->map->collect, coef, 0x00AA00);
		printf("player->map->collect->x %d, player->map->collect->y %d\n", player->map->collect->x, player->map->collect->y);
		player->map->collect = player->map->collect->next;
	}
	while (player->map->start)
	{
		player->map->start->x *= coef;
		player->map->start->y *= coef;
		ft_draw_square(player->img, player->map->start, coef, 0x000099);
		printf("player->map->start->x %d, player->map->start->y %d\n", player->map->start->x, player->map->start->y);
		player->map->start = player->map->start->next;
	}
	while (player->map->end)
	{
		player->map->end->x *= coef;
		player->map->end->y *= coef;
		ft_draw_square(player->img, player->map->end, coef, 0x660000);
		printf("player->map->end->x %d, player->map->end->y %d\n", player->map->end->x, player->map->end->y);
		player->map->end = player->map->end->next;
	}
	// Keep in mind that coordonates are important! Don't mess with it !
	mlx_put_image_to_window(player->screen->mlx, player->screen->win, player->img->def, 0, 0);
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
	printf("%s, %d\n", file[1], player->fd);
	player->map = ft_parse_map(player->fd, file);
	// Attention ici checker que 1 seule pos de depart
	player->pole_pos = ft_init_point(player->map->start->x, player->map->start->y, 0);
	player->screen = ft_init_screen(title, scr_width, scr_height);
	// A creer fn init img 
	player->img = ft_init_img(player, 64);
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
		ft_draw_wall(player);
		mlx_hook(player->screen->win, 17, 1L << 2, ft_hook_close_mlx, player);
		mlx_hook(player->screen->win, 2, 1L << 0, key_hook, player);
	// 	mlx_loop_hook(img->mlx, ft_display_screen, img);
		mlx_loop(player->screen->mlx);
		ft_clean_player(player);
	}
	else
		ft_parse_map_error(22);
	return (0);
}

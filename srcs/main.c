#include "../includes/so_long.h"

typedef struct	s_data
{
	void	*mlx;
	void	*win;
}				t_data;

/*typedef struct	s_img
{
	void	*def;
	void	*addr;
	int		bpp;
	int		len;
	int		end;
	void	*mlx;
	void	*win;
	int		width;
	int		height;
}				t_img;*/

// Enlever le param start qui ne sert plus rien
// remplacer img par player ?
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

// Attention a modif img->bpp * 2 et 64
int		ft_hook_key_s(int keycode, t_img *img)
{
	if (keycode == 1 && img->coord->y < img->height - 64 * 2)
	{
		ft_draw_square(img, img->coord, 64, 0x993366);
		img->coord->y += img->bpp * 2;
		img->coord->pos++;
		ft_draw_square(img, img->coord, 64, 0x00AAAA);
		mlx_put_image_to_window(img->mlx, img->win, img->def, img->coord->x, img->coord->y);
		printf("During hook s: img->coord->y %d, img->coord->x %d img->coord->pos %d\n", img->coord->y, img->coord->x, img->coord->pos);
	}
	return (0);
}

// Attention a modif img->bpp * 2 et 64
int		ft_hook_key_w(int keycode, t_img *img)
{
	if (keycode == 13 && img->coord->y > 64)
	{
		ft_draw_square(img, img->coord, 64, 0x993366);
		img->coord->y -= img->bpp * 2;
		img->coord->pos++;
		ft_draw_square(img, img->coord, 64, 0x00AAAA);
	// Keep in mind that coordonates are important! Don't mess with it !
		mlx_put_image_to_window(img->mlx, img->win, img->def, img->coord->x, img->coord->y);
		printf("During hook w: img->coord->y %d, img->coord->x %d img->coord->pos %d\n", img->coord->y, img->coord->x, img->coord->pos);
	}
	return (0);
}

// Attention a modif img->bpp * 2 et 64
int		ft_hook_key_a(int keycode, t_img *img)
{
	if (keycode == 0 && img->coord->x > 64)
	{
		ft_draw_square(img, img->coord, 64, 0x993366);
		img->coord->x -= img->bpp * 2;
		img->coord->pos++;
		ft_draw_square(img, img->coord, 64, 0x00AAAA);
	// Keep in mind that coordonates are important! Don't mess with it !
		mlx_put_image_to_window(img->mlx, img->win, img->def, img->coord->x, img->coord->y);
		printf("During hook a: img->coord->y %d, img->coord->x %d img->coord->pos %d\n", img->coord->y, img->coord->x, img->coord->pos);
	}
	return (0);
}

// Attention a modif img->bpp * 2 et 64
int		ft_hook_key_d(int keycode, t_img *img)
{
	if (keycode == 2 && img->coord->x < img->width - 64 * 2)
	{
		ft_draw_square(img, img->coord, 64, 0x993366);
		img->coord->x += img->bpp * 2;
		img->coord->pos++;
		ft_draw_square(img, img->coord, 64, 0x00AAAA);
	// Keep in mind that coordonates are important! Don't mess with it !
		mlx_put_image_to_window(img->mlx, img->win, img->def, img->coord->x, img->coord->y);
		printf("During hook d: img->coord->y %d, img->coord->x %d img->coord->pos %d\n", img->coord->y, img->coord->x, img->coord->pos);
	}
	return (0);
}

int		key_hook(int keycode, t_img *img)
{
	ft_hook_key_esc(keycode, img);
	ft_hook_key_a(keycode, img);
	ft_hook_key_s(keycode, img);
	ft_hook_key_d(keycode, img);
	ft_hook_key_w(keycode, img);
	return (0);
}

int	ft_display_screen(t_img *img)
{
	int color;

	color = 0x993366;
	ft_fill_screen(img, color);
	//ft_draw_square(img, img->coord, 64, 0x00BBBB);
	// Keep in mind that coordonates are important! Don't mess with it !
	mlx_put_image_to_window(img->mlx, img->win, img->def, img->coord->x, img->coord->y);
	return (1);
}
void	ft_draw_wall(t_img *img, t_map *map)
{

	ft_fill_screen(img, 0x993366);
	while (map->wall)
	{
		map->wall->x *= 64;
		map->wall->y *= 64;
		ft_draw_square(img, map->wall, 64, 0x555555);
		printf("map->wall->x %d, map->wall->y %d\n", map->wall->x, map->wall->y);
		map->wall = map->wall->next;
	}
	while (map->collect)
	{
		map->collect->x *= 64;
		map->collect->y *= 64;
		ft_draw_square(img, map->collect, 64, 0x00AA00);
		printf("map->collect->x %d, map->collect->y %d\n", map->collect->x, map->collect->y);
		map->collect = map->collect->next;
	}
	while (map->start)
	{
		map->start->x *= 64;
		map->start->y *= 64;
		ft_draw_square(img, map->start, 64, 0x000099);
		printf("map->start->x %d, map->start->y %d\n", map->start->x, map->start->y);
		map->start = map->start->next;
	}
	while (map->end)
	{
		map->end->x *= 64;
		map->end->y *= 64;
		ft_draw_square(img, map->end, 64, 0x660000);
		printf("map->end->x %d, map->end->y %d\n", map->end->x, map->end->y);
		map->end = map->end->next;
	}
	// Keep in mind that coordonates are important! Don't mess with it !
	mlx_put_image_to_window(img->mlx, img->win, img->def, 0, 0);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_map	*map;
	t_img	*img;
	char	*title;

	title = ft_strdup("So_long, and thanks for all the fishes");
	if (argc == 2)
	{
		// Ouverture du fichier
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			ft_parse_map_error(errno);
		map = ft_parse_map(fd, argv);
		// debugage
		print_info_map(map);

		// mlx
		//img = &(t_img){NULL, NULL, 0, 0, 0, NULL, NULL, map->cols * 64, map->lines * 64, NULL};
		img = &(t_img){NULL, NULL, 0, 0, 0, NULL, NULL, 1366, 720, NULL};
		ft_get_img_mlx(img);
		ft_get_img_win(img, title);
		ft_get_img_def(img);
		ft_get_img_addr(img);
		//img->coord = ft_init_point(0, 0, 0);
		img->coord = ft_init_point(-128, -128, 0);
		printf("Before hook: img->coord->y %d, img->coord->x %d\n", img->coord->y, img->coord->x);
		ft_draw_wall(img, map);
		// events
		printf("after display screen: img->coord->y %d, img->coord->x %d img->coord->pos %d\n", img->coord->y, img->coord->x, img->coord->pos);
		// gestion click croix rouge
		mlx_hook(img->win, 17, 1L << 2, ft_hook_close_mlx, img);
		// gestion des touches
		mlx_hook(img->win, 2, 1L << 0, key_hook, img);
		printf("After hook: img->coord->y %d, img->coord->x %d\n", img->coord->y, img->coord->x);
	// 	mlx_loop_hook(img->mlx, ft_display_screen, img);
		mlx_loop(img->mlx);
		free(title);
		// fin mlx

		// Nettoyage de la map en entier
		ft_clean_map(map);
		// Fermeture du file descriptor
		close(fd);
	}
	else
		ft_parse_map_error(22);
	return (0);
}

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
void	ft_draw_polyg(t_img *img, t_point *start, int size, int color)
{
	int	x;
	int y;
	(void)start;

	y = 0;
	//while (y < img->height)
	while (y < size)
	{
		x = 0;
		//while (x < img->width)
		while (x < size)
			ft_mlx_pixel_put(img, x++, y, color);
		y++;
	}
//	mlx_put_image_to_window(img->mlx, img->win, img->def, img->coord->x, img->coord->y);
}

// Attention a modif img->bpp * 2 et 64
int		ft_hook_key_s(int keycode, t_img *img)
{
	if (keycode == 1 && img->coord->y < img->height - 64 * 2)
	{
		ft_draw_polyg(img, img->coord, 64, 0x993366);
		img->coord->y += img->bpp * 2;
		img->coord->pos++;
		ft_draw_polyg(img, img->coord, 64, 0x00AAAA);
		mlx_put_image_to_window(img->mlx, img->win, img->def, img->coord->x, img->coord->y);
	//	img->coord->y += img->bpp * 2;
		printf("During hook s: img->coord->y %d, img->coord->x %d img->coord->pos %d\n", img->coord->y, img->coord->x, img->coord->pos);
	}
	return (0);
}

// Attention a modif img->bpp * 2 et 64
int		ft_hook_key_w(int keycode, t_img *img)
{
	if (keycode == 13 && img->coord->y > 64)
	{
		ft_draw_polyg(img, img->coord, 64, 0x993366);
		img->coord->y -= img->bpp * 2;
		img->coord->pos++;
		ft_draw_polyg(img, img->coord, 64, 0x00AAAA);
		mlx_put_image_to_window(img->mlx, img->win, img->def, img->coord->x, img->coord->y);
	//	img->coord->y -= img->bpp * 2;
		printf("During hook w: img->coord->y %d, img->coord->x %d img->coord->pos %d\n", img->coord->y, img->coord->x, img->coord->pos);
	}
	return (0);
}

int		ft_hook_key_a(int keycode, t_img *img)
{
	if (keycode == 0 && img->coord->x > 64)
	{
		ft_draw_polyg(img, img->coord, 64, 0x993366);
		img->coord->x -= img->bpp * 2;
		img->coord->pos++;
		ft_draw_polyg(img, img->coord, 64, 0x00AAAA);
		mlx_put_image_to_window(img->mlx, img->win, img->def, img->coord->x, img->coord->y);
		printf("During hook a: img->coord->y %d, img->coord->x %d img->coord->pos %d\n", img->coord->y, img->coord->x, img->coord->pos);
	}
	return (0);
}

int		ft_hook_key_d(int keycode, t_img *img)
{
	if (keycode == 2 && img->coord->x < img->width - 64 * 2)
	{
		ft_draw_polyg(img, img->coord, 64, 0x993366);
		img->coord->x += img->bpp * 2;
		img->coord->pos++;
		ft_draw_polyg(img, img->coord, 64, 0x00AAAA);
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
//	char	*title;
//	t_img	*img_sq;
//	t_img	*img;

	color = 0x993366;
//	title = ft_strdup("So_long, and thanks for all the fishes");
//	img = &(t_img){NULL, NULL, 0, 0, 0, NULL, NULL, 13 * 64, 5 * 64, NULL};
//	ft_get_img_mlx(img);
//	ft_get_img_win(img, title);
//	ft_get_img_def(img);
//	ft_get_img_addr(img);
	ft_fill_screen(img, color);
//	img->coord = ft_init_point(64, 64, 0);
//	ft_draw_polyg(img, &(t_point){64,64,0, NULL}, 64, color);
//	img->coord = ft_init_point(64, 64, 0);
	ft_draw_polyg(img, img->coord, 64, 0x00BBBB);
	mlx_put_image_to_window(img->mlx, img->win, img->def, img->coord->x, img->coord->y);
//	mlx_destroy_image(img->mlx, img->def);
//	free(img->coord);
//	free(title);
	return (1);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_map	*map;
	t_img	*img;
//	t_img	*img_sq;
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
	//	int color = 0x993366;
		img = &(t_img){NULL, NULL, 0, 0, 0, NULL, NULL, map->cols * 64, map->lines * 64, NULL};

		ft_get_img_mlx(img);
		ft_get_img_win(img, title);
		ft_get_img_def(img);
		ft_get_img_addr(img);
		img->coord = ft_init_point(0, 0, 0);
	//	img->coord = ft_init_point(64, 64, 0);
		printf("Before hook: img->coord->y %d, img->coord->x %d\n", img->coord->y, img->coord->x);
		// Nouvelle image representant un carre que je vais essayer de deplacer sur la map
//		img_sq = &(t_img){NULL, NULL, 0, 0, 0, img->mlx, img->win, 64, 64};
//		ft_get_img_def(img_sq);
//		ft_get_img_addr(img_sq);

		// front-end
//		ft_fill_screen(img, color);
//		ft_draw_screen_grid_map(img, 0x00FF00, map);
//		ft_draw_screen_grid_bpp(img, 0x000000);
//		t_point	*start = NULL;

//		start = ft_init_point(64, 64, 0);
//		ft_draw_polyg(img_sq, start, 64, 0x00BBBB);
	//	ft_draw_polyg(img, start, 64, 0x00BBBB);

		// events
		//mlx_key_hook(img->win, key_hook, img_sq);
		ft_display_screen(img);
		printf("after display screen: img->coord->y %d, img->coord->x %d img->coord->pos %d\n", img->coord->y, img->coord->x, img->coord->pos);
	//	ft_draw_polyg(img, &(t_point){64,64,0, NULL}, 64, 0x00AAAA);
	//	mlx_key_hook(img->win, key_hook, img);
		// gestion touche esc pressee
		//	mlx_hook(img->win, 2, 1L << 0, ft_hook_key_esc, img);
		// gestion touche s pressee
		//	mlx_hook(img->win, 2, 1L << 0, ft_hook_key_s, img);
		// gestion click croix rouge
		mlx_hook(img->win, 17, 1L << 2, ft_hook_close_mlx, img);
		mlx_hook(img->win, 2, 1L << 0, key_hook, img);
		printf("After hook: img->coord->y %d, img->coord->x %d\n", img->coord->y, img->coord->x);
	 	mlx_loop_hook(img->mlx, ft_display_screen, img);
		mlx_loop(img->mlx);
		free(title);
//		free(start);
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

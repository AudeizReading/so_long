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

void	ft_draw_polyg(t_img *img, t_point *start, int size, int color)
{
	int	x;
	int y;

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
	mlx_put_image_to_window(img->mlx, img->win, img->def, start->x, start->y);
}

int		ft_hook_key_s(int keycode, t_img *img)
{
	t_point	*start = NULL;

	if (keycode == 1)
	{
		start = ft_init_point(64, 64, 0);
		ft_draw_polyg(img, start, 64, 0x993366);
		//start->y += img->height;
		start->y += img->bpp;
		ft_draw_polyg(img, start, 64, 0x00AAAA);
		printf("start->y %d, start->x %d\n", start->y, start->x);
	}
	return (0);
}

int		key_hook(int keycode, t_img *img)
{
	if (keycode == 53)
		ft_hook_close_mlx(img);
	if (keycode == 0) // a
		;
	if (keycode == 1) // s
		ft_hook_key_s(keycode, img);
	if (keycode == 2) // d
		;
	if (keycode == 13) // w
		;
	return (0);
}

int	ft_display_screen(t_img *img)
{
	int color;
	t_img	*img_sq;
	t_point	*start = NULL;

	color = 0x993366;
	ft_fill_screen(img, color);
	img_sq = &(t_img){NULL, NULL, 0, 0, 0, img->mlx, img->win, 64, 64};
	ft_get_img_def(img_sq);
	ft_get_img_addr(img_sq);
	start = ft_init_point(64, 64, 0);
	ft_draw_polyg(img_sq, start, 64, 0x00BBBB);
	mlx_key_hook(img->win, key_hook, img);
	mlx_destroy_image(img_sq->mlx, img_sq->def);
	free(start);
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
//		img = &(t_img){NULL, NULL, 0, 0, 0, NULL, NULL, 640, 480};
		img = &(t_img){NULL, NULL, 0, 0, 0, NULL, NULL, map->cols * 64, map->lines * 64};

		ft_get_img_mlx(img);
		ft_get_img_win(img, title);
		ft_get_img_def(img);
		ft_get_img_addr(img);
		// Nouvelle image representant un carre que je vais essayer de deplacer sur la map
//		img_sq = &(t_img){NULL, NULL, 0, 0, 0, img->mlx, img->win, 64, 64};
//		ft_get_img_def(img_sq);
//		ft_get_img_addr(img_sq);

		// front-end
//		ft_fill_screen(img, color);
//		ft_draw_screen_grid_map(img, 0x00FF00, map);
//		ft_draw_screen_grid_bpp(img, 0x000000);
		mlx_loop_hook(img->mlx, ft_display_screen, img);
//		t_point	*start = NULL;

//		start = ft_init_point(64, 64, 0);
//		ft_draw_polyg(img_sq, start, 64, 0x00BBBB);
	//	ft_draw_polyg(img, start, 64, 0x00BBBB);

		// events
		//mlx_key_hook(img->win, key_hook, img_sq);
		mlx_key_hook(img->win, key_hook, img);
		// gestion touche esc pressee
	//	mlx_hook(img->win, 2, 1L << 0, ft_hook_key_esc, img);
		// gestion touche s pressee
//		mlx_hook(img->win, 2, 1L << 0, ft_hook_key_s, img);
		// gestion click croix rouge
		mlx_hook(img->win, 17, 1L << 2, ft_hook_close_mlx, img);
	//	mlx_loop_hook(img->mlx, key_hook, img);
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

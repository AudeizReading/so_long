#include "../includes/so_long.h"

typedef struct	s_data
{
	void	*mlx;
	void	*win;
}				t_data;

typedef struct	s_img
{
	void	*def;
	void	*addr;
	int		bits_per_pix;
	int		line_len;
	int		endian;
//	t_data	*data;
	void	*mlx;
	void	*win;
}				t_img;

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * img->line_len + x * (img->bits_per_pix / 8));
	dst = img->addr + offset;
	*(unsigned *)dst = color;
}

int		ft_close(t_img *img)
{
	//mlx_destroy_image(img->data->mlx, img->def);
	//mlx_destroy_window(img->data->mlx, img->data->win);
	mlx_destroy_image(img->mlx, img->def);
	mlx_destroy_window(img->mlx, img->win);
	exit(EXIT_SUCCESS);
	return (0);
}

int		key_hook(int keycode, t_img *img)
{
	if (keycode == 53)
		ft_close(img);
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_map	*map;
	t_img	*img;
	int	x;
	int	y;
	int	width;
	int	height;

	width = 640;
	height = 480;
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
		img = &(t_img){NULL, NULL, 0, 0, 0, NULL, NULL};
	//	img->data = &(t_data){NULL, NULL};
		//img->data->mlx = mlx_init();
		//if (!img->data->mlx)
		img->mlx = mlx_init();
		if (!img->mlx)
			exit(EXIT_FAILURE);
		//img->data->win = mlx_new_window(img->data->mlx, width, height, "So_long, and thanks for all the fishes");
		//if (!img->data->win)
		img->win = mlx_new_window(img->mlx, width, height, "So_long, and thanks for all the fishes");
		if (!img->win)
			exit(EXIT_FAILURE);
		int color = 0x993366;

		//img->def = mlx_new_image(img->data->mlx, width, height);
		img->def = mlx_new_image(img->mlx, width, height);
		if (!img->def)
			exit(EXIT_FAILURE);
		img->addr = mlx_get_data_addr(img->def, &img->bits_per_pix, &img->line_len, &img->endian);
		if (!img->addr)
			exit(EXIT_FAILURE);

		// debug valeurs struct ing
	//	ft_putendl_fd("Nombre de bits par pixel:", 1);
	//	ft_putnbr_fd(img->bits_per_pix, 1);
	//	ft_putchar_fd('\n', 1);
	//	ft_putendl_fd("Valeur de line_len (img):", 1);
	//	ft_putnbr_fd(img->line_len, 1);
	//	ft_putchar_fd('\n', 1);
		// fin debug

		y = 0;
		while (y < height)
		{
			x = 0;
		//	color -= 640;
			while (x < width)
			{
			/*	if (x && !(x % 32))
					ft_mlx_pixel_put(img, x++, y, INT_MAX);
				else*/ if (x && !(x % (640 / map->cols)))
					ft_mlx_pixel_put(img, x++, y, 0x00FF00);
			/*	else if (x && y && !(y % 32))
					ft_mlx_pixel_put(img, x++, y, INT_MAX);*/
				else if (x && y && !(y % (480 / map->lines)))
					ft_mlx_pixel_put(img, x++, y, 0x00FF00);
				else
					ft_mlx_pixel_put(img, x++, y, color/*++*/);
			}
		//	color++;
			y++;
		}
		//mlx_put_image_to_window(img->data->mlx, img->data->win, img->def, 0, 0);
		mlx_put_image_to_window(img->mlx, img->win, img->def, 0, 0);

		//mlx_key_hook(img->data->win, key_hook, img);
		//mlx_hook(img->data->win, 17, 1L << 2, ft_close, img);
		//mlx_loop(img->data->mlx); // fin mlx
		mlx_key_hook(img->win, key_hook, img);
		mlx_hook(img->win, 17, 1L << 2, ft_close, img);
		mlx_loop(img->mlx); // fin mlx

		// Nettoyage de la map en entier
		ft_clean_map(map);
		// Fermeture du file descriptor
		close(fd);
	}
	else
		ft_parse_map_error(22);
	return (0);
}

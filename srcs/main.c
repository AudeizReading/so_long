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
}				t_img;

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * img->line_len + x * (img->bits_per_pix / 8));
	dst = img->addr + offset;
	*(unsigned *)dst = color;
}

int		key_hook(int keycode, t_data *data)
{
	ft_putendl_fd("Hello from key_hook", 1);
	ft_putstr_fd("keycode; ", 1);
	ft_putnbr_fd(keycode, 1);
	ft_putchar_fd('\n', 1);
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(EXIT_SUCCESS);
	//	ft_clean_map(map);
	//	close(fd);
	}
	return (0);
}

int		mouse_hook(int button, int x, int y, t_data *data)
{
	(void)data;
	ft_putendl_fd("Hello from mouse_hook", 1);
	ft_putstr_fd("button; ", 1);
	ft_putnbr_fd(button, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("x; ", 1);
	ft_putnbr_fd(x, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("y; ", 1);
	ft_putnbr_fd(y, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
int	main(int argc, char **argv)
{
	int		fd;
	t_map	*map;
//	void	*mlx;
//	void	*win;
	t_img	*img;
	t_data	*data;

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
		data = &(t_data){NULL, NULL};
		//mlx = mlx_init();
		data->mlx = mlx_init();
		//if (!mlx)
		if (!data->mlx)
			exit(EXIT_FAILURE);
	//	win = mlx_new_window(mlx, 600, 400, "So_long, and thanks for all the fishes");
		//win = mlx_new_window(mlx, 1366, 768, "So_long, and thanks for all the fishes");
		//data->win = mlx_new_window(data->mlx, 1366, 768, "So_long, and thanks for all the fishes");
		data->win = mlx_new_window(data->mlx, 640, 480, "So_long, and thanks for all the fishes");
		//if (!win)
		if (!data->win)
			exit(EXIT_FAILURE);
		int	x;
		int	y;
		int color = 0x993366;

		img = &(t_img){NULL, NULL, 0, 0, 0};
//		img->def = mlx_new_image(mlx, 600, 400);
	//	img->def = mlx_new_image(mlx, 1366, 768);
		//img->def = mlx_new_image(data->mlx, 1366, 768);
		img->def = mlx_new_image(data->mlx, 640, 480);
		if (!img->def)
			exit(EXIT_FAILURE);
		img->addr = mlx_get_data_addr(img->def, &img->bits_per_pix, &img->line_len, &img->endian);
		if (!img->addr)
			exit(EXIT_FAILURE);
		ft_putendl_fd("Nombre de bits par pixel:", 1);
		ft_putnbr_fd(img->bits_per_pix, 1);
		ft_putchar_fd('\n', 1);
		ft_putendl_fd("Valeur de line_len (img):", 1);
		ft_putnbr_fd(img->line_len, 1);
		ft_putchar_fd('\n', 1);
		y = 0;
	//	while (y < 400)
	//	while (y < 768)
		while (y < 480)
		{
			x = 0;
		//	color -= 640;
		//	while (x < 600)
		//	while (x < 1366)
			while (x < 640)
			{
				//mlx_pixel_put(mlx, win, x++, y, ft_get_trgb(1, 128, 0, 128));
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
	//else
	//	ft_mlx_pixel_put(img, x++, y, color/*++*/);
		}
		//mlx_put_image_to_window(mlx, win, img->def, 0, 0);
		mlx_put_image_to_window(data->mlx, data->win, img->def, 0, 0);

		mlx_key_hook(data->win, key_hook, data);
		mlx_mouse_hook(data->win, mouse_hook, data);
		mlx_loop(data->mlx); // fin mlx
		//mlx_loop(mlx); // fin mlx

		// Nettoyage de la map en entier
		ft_clean_map(map);
		// Fermeture du file descriptor
		close(fd);
	}
	else
		ft_parse_map_error(22);
	return (0);
}

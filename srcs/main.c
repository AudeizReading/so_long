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
	int		bpp;
	int		len;
	int		end;
	void	*mlx;
	void	*win;
	int		width;
	int		height;
}				t_img;

void	ft_get_img_mlx(t_img *img)
{
	img->mlx = mlx_init();
	if (!img->mlx)
		exit(EXIT_FAILURE);
}

void	ft_get_img_win(t_img *img, char *title)
{
	img->win = mlx_new_window(img->mlx, img->width, img->height, title);
	if (!img->win)
		exit(EXIT_FAILURE);
}

void	ft_get_img_def(t_img *img)
{
	img->def = mlx_new_image(img->mlx, img->width, img->height);
	if (!img->def)
		exit(EXIT_FAILURE);
}

void	ft_get_img_addr(t_img *img)
{
	img->addr = mlx_get_data_addr(img->def, &img->bpp, &img->len, &img->end);
	if (!img->addr)
		exit(EXIT_FAILURE);
}

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * img->len + x * (img->bpp / 8));
	dst = img->addr + offset;
	*(unsigned *)dst = color;
}

int		ft_close(t_img *img)
{
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
		int color = 0x993366;
		img = &(t_img){NULL, NULL, 0, 0, 0, NULL, NULL, 640, 480};

		ft_get_img_mlx(img);
		ft_get_img_win(img, title);
		ft_get_img_def(img);
		ft_get_img_addr(img);
		y = 0;
		while (y < img->height)
		{
			x = 0;
		//	color -= 640;
			while (x < img->width)
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
		mlx_put_image_to_window(img->mlx, img->win, img->def, 0, 0);

		mlx_key_hook(img->win, key_hook, img);
		mlx_hook(img->win, 17, 1L << 2, ft_close, img);
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

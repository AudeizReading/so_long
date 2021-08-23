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

void	ft_fill_screen(t_img *img, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			ft_mlx_pixel_put(img, x++, y, color);
		}
		y++;
	}
	mlx_put_image_to_window(img->mlx, img->win, img->def, 0, 0);
}

void	ft_draw_grid_map(t_img *img, int color, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			if (x && !(x % (img->width / map->cols))) 
				ft_mlx_pixel_put(img, x++, y, color);
			else if (x && y && !(y % (img->height / map->lines)))
				ft_mlx_pixel_put(img, x++, y, color);
			else
				x++;
		}
		y++;
	}
	mlx_put_image_to_window(img->mlx, img->win, img->def, 0, 0);
}

void	ft_draw_grid_bpp(t_img *img, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			if (x && !(x % img->bpp)) 
				ft_mlx_pixel_put(img, x++, y, color);
			else if (x && y && !(y % img->bpp))
				ft_mlx_pixel_put(img, x++, y, color);
			else
				x++;
		}
		y++;
	}
	mlx_put_image_to_window(img->mlx, img->win, img->def, 0, 0);
}

void	ft_draw_square(t_img *img, t_point *start, int color)
{
	int	x_offset;
	int	y_offset;

	x_offset = start->x + img->width;
	y_offset = start->y + img->height;
	while (start->y < y_offset)
	{
		start->x = x_offset - img->width;
		while (start->x < x_offset)
			ft_mlx_pixel_put(img, start->x++, start->y, color);
		start->y++;
	}
	start->x = x_offset - img->width;
	start->y = y_offset - img->height;
	mlx_put_image_to_window(img->mlx, img->win, img->def, start->x, start->y);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_map	*map;
	t_img	*img;
	t_img	*img_sq;
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
		img_sq = &(t_img){NULL, NULL, 0, 0, 0, img->mlx, img->win, 64, 64};
		ft_get_img_def(img_sq);
		ft_get_img_addr(img_sq);

		// front-end
		ft_fill_screen(img, color);
		ft_draw_grid_map(img, 0x00FF00, map);
		ft_draw_grid_bpp(img, 0x000000);
		//ft_fill_screen(img_sq, 0x00BBBB);
		//mlx_put_image_to_window(img_sq->mlx, img_sq->win, img_sq->def, 64, 64);
		t_point	*start = NULL;

		start->x = 64;
		start->y = 64;
		ft_draw_square(img_sq, start, 0x00BBBB);

		// events
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

#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	int		fd;
	t_map	*map;
	void	*mlx;
	void	*win;

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
		mlx = mlx_init();
		if (!mlx)
			exit(EXIT_FAILURE);
		win = mlx_new_window(mlx, 600, 400, "So_long, and thanks for all the fishes");
		if (!win)
			exit(EXIT_FAILURE);
		int	x;
		int	y;

		y = 0;
		while (y <= 400)
		{
			x = 0;
			while (x <= 600)
			{
				mlx_pixel_put(mlx, win, x++, y, ft_get_trgb(1, 128, 0, 128));
			}
			y++;
		}
		mlx_loop(mlx); // fin mlx
		// Nettoyage de la map en entier
		ft_clean_map(map);
		// Fermeture du file descriptor
		close(fd);
	}
	else
		ft_parse_map_error(22);
	return (0);
}

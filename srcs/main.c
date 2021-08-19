#include "../includes/so_long.h"

void	print_info_map(t_map *map)
{
	ft_putendl_fd("------------MAP------------------", 1);
	ft_print_map(map->first_line);
	ft_putnbr_fd(map->lines, 1);
	ft_putendl_fd(" maillons", 1);
	ft_putendl_fd("Dimensions map :", 1);
	ft_putnbr_fd(map->cols, 1);
	ft_putstr_fd(" x ", 1);
	ft_putnbr_fd(map->lines, 1);
	ft_putstr_fd("\n", 1);
	ft_putendl_fd("---------------------------------", 1);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_map	*map;

//	map  = &(t_map){0, 0, NULL, NULL, NULL, NULL, NULL};
	map = ft_init_map();
	if (argc == 2)
	{
		// Ouverture du fichier
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			ft_parse_map_error(errno);
		// Verification que le nom de fichier se termine en .ber
		if (!ft_is_map_file(argv[1], ".ber"))
			ft_parse_map_error(1026);
		// Recuperation de la map
		map->first_line = ft_get_map(fd);
		if (!map->first_line)
			ft_parse_map_error(1025);
		// Parametrage du nombre de lignes et de colonnes de la map
		map->lines = ft_map_size(map->first_line);
		map->cols = map->first_line->len;
		// debugage
		print_info_map(map);
		// Verif presence des chars 0 1 C E P
		if(!ft_check_valid_characters(map->first_line))
			ft_parse_map_error(1029);
		// Verif map rectangulaire
		if (!ft_is_rectangular_map(map->first_line))
			ft_parse_map_error(1027);
		// Recup de la (ou des) position de depart
		map->start = ft_has_object(map->first_line, 'P', 0);
		if (!map->start)
			ft_parse_map_error(1032);
		ft_putendl_fd("Liste des points de depart", 1);
		ft_print_point_list(map->start);
		// Recup des positions des collectibles
		map->collect = ft_has_object(map->first_line, 'C', 0);
		if (!map->collect)
			ft_parse_map_error(1031);
		ft_putendl_fd("Liste des points de collectibles", 1);
		ft_print_point_list(map->collect);
		// Recup de la (ou des) position de sortie
		map->end = ft_has_object(map->first_line, 'E', 0);
		if (!map->end)
			ft_parse_map_error(1030);
		ft_putendl_fd("Liste des points de sortie", 1);
		ft_print_point_list(map->end);
		// Recup des positions des murs
		map->wall = ft_has_object(map->first_line, '1', 0);
		if (!map->wall || !ft_check_wall(map->first_line))
			ft_parse_map_error(1028);
		// Liberation des points
		ft_point_clear(&map->start, free);
		ft_point_clear(&map->collect, free);
		ft_point_clear(&map->end, free);
		ft_point_clear(&map->wall, free);
		// Liberation de la map
		ft_map_clear(&map->first_line, free);
		free(map);
		// Fermeture du file descriptor
		close(fd);
	}
	else
		ft_parse_map_error(22);
	return (0);
}

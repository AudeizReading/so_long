#include "../includes/so_long.h"

typedef struct	s_map
{
	size_t	cols;
	size_t	lines;
//	t_point	*start;
//	t_point	*collect;
//	t_point	*end;
	t_line	*first_line;
}				t_map;

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

void	ft_check_valid_characters(t_line *map)
{
	char	*p_content;

	while (map)
	{
		p_content = map->content;
		while (*p_content)
		{
			if (!ft_strchr("01CEP", *p_content))
				ft_parse_map_error(1029);
			/*else
				ft_putchar_fd(*p_content, 1);*/
			p_content++;
		}
		map = map->next;
	}
}

t_bool	ft_is_rectangular_map(t_line *map)
{
	size_t	first_line_len;

	first_line_len = map->len;
	while (map)
	{
		if (first_line_len != map->len)
			ft_parse_map_error(1027);
		map = map->next;
	}
	return (e_true);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_map	*map;

	map  = &(t_map){0, 0, NULL};
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			ft_parse_map_error(errno);
		if (!ft_is_map_file(argv[1], ".ber"))
			ft_parse_map_error(1026);
		map->first_line = ft_get_map(fd);
		if (!map->first_line)
			ft_parse_map_error(1025);
		map->lines = ft_map_size(map->first_line);
		map->cols = map->first_line->len;
		print_info_map(map);
		/* Test liste chainee struct point */
		/*t_point	*start_test = NULL;
		t_point	*point_test;
		int		i = 0;

		while (i < 3)
		{
			point_test = ft_init_point(8, 3, i);
			ft_point_addback(&start_test, point_test);
			ft_putnbr_fd(i, 1);
			ft_putendl_fd(" i", 1);
			i++;
		}
		ft_print_point_list(start_test);
		ft_point_clear(&start_test, free);*/
		ft_check_valid_characters(map->first_line);
		if (ft_is_rectangular_map(map->first_line))
			ft_putendl_fd("Map is rectangular", 1);
		ft_map_clear(&map->first_line, free);
		close(fd);
	}
	else
		ft_parse_map_error(22);
	return (0);
}

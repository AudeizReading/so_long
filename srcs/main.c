#include "../includes/so_long.h"

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct	s_map
{
	size_t	cols;
	size_t	lines;
//	t_point	start;
//	t_point	collect;
//	t_point	end;
//	t_list	*line;
}				t_map;

int		main(int argc, char **argv)
{
	int		fd;
	int		gnl;
	char	*line;
	t_map	*map;
	t_list	*map_line;
	t_list	*tmp;

	gnl = 1;
	line = NULL;
	map_line = NULL;
	map  = &(t_map){0, 0, /*{0, 0}, {0, 0}*/};
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			ft_parse_map_error(errno);
		if (!ft_is_map_file(argv[1], ".ber"))
			ft_parse_map_error(79);
		ft_putstr_fd("\n", 1);
		while (gnl > 0)
		{
			gnl = get_next_line(fd, &line);
			// Here check if map is rectangular or have 0, 1, C, E and P chars
			// Check if it is wall all around"
			ft_putendl_fd(line, 1);
			tmp = ft_new_mapline(line);
			if (gnl)
				ft_lstadd_back(&map_line, tmp);/**/
			free(line);
		}
		if (gnl == -1)
			ft_parse_map_error(errno);
		ft_putendl_fd("------MAP------------------------", 1);
		ft_print_list(map_line);
		ft_putendl_fd("---------------------------------", 1);
		ft_putnbr_fd(ft_lstsize(map_line), 1);
		ft_putendl_fd(" maillons", 1);
		ft_lstclear(&tmp, free);
		ft_lstclear(&map_line, free);
		close(fd);
	}
	else
		ft_parse_map_error(22);
	return (0);
}

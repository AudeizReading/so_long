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
	t_point	start;
	t_point	collect;
	t_point	end;
	t_list	map_line;
}				t_map;

/*t_bool	ft_is_map_file(char *filename, char *ext)
{
	size_t	name_len;
	size_t	ext_len;

	name_len = ft_strlen(filename);
	ext_len = ft_strlen(ext);
	if (!ft_strncmp(filename + (name_len - ext_len), ext, ext_len))
		return (e_true);
	return (e_false);
}*/

int		main(int argc, char **argv)
{
	int		fd;
	int		gnl;
	char	*line;

	gnl = 1;
	line = NULL;
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
			free(line);
		}
		if (gnl == -1)
			ft_parse_map_error(errno);
		close(fd);
	}
	else
		ft_parse_map_error(22);
	return (0);
}

#include "../includes/so_long.h"

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
		ft_putendl_fd(argv[1] + (ft_strlen(argv[1]) - ft_strlen(".ber") - 1), 1);
		// Here checking if the file got the good extensions
		while (gnl > 0)
		{
			gnl = get_next_line(fd, &line);
			// Here check if map is rectangular or have 0, 1, C, E and P chars
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

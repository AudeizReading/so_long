#include <fcntl.h>
#include <unistd.h>
#include "../includes/so_long.h"

int		main(void)
{
	int		fd;
	int		gnl;
	char	*line;

	gnl = 1;
	line = NULL;
	fd = open("main.c", O_RDONLY);
	if (fd == -1)
		ft_putstr_fd("Error\n", 1);
	while (gnl > 0)
	{
		gnl = get_next_line(fd, &line);
		ft_putendl_fd(line, 1);
		free(line);
	}
	if (gnl == -1)
		ft_putendl_fd("Error\ngnl a eu un souci\n", 1);
	close(fd);
	ft_putstr_fd("Ca fonctionne\n", 1);
	return (0);
}

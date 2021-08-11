#include "../includes/so_long.h"

void	ft_puterror(void)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(strerror(errno), 2);
	exit(EXIT_FAILURE);
}

int		main(void)
{
	int		fd;
	int		gnl;
	char	*line;

	gnl = 1;
	line = NULL;
	fd = open("srcs/main.c", O_RDONLY);
	//fd = open("main.c", O_RDONLY);
	if (fd == -1)
	{
		ft_puterror();
	}
	while (gnl > 0)
	{
		gnl = get_next_line(fd, &line);
		ft_putendl_fd(line, 1);
		free(line);
	}
	if (gnl == -1)
	{
		errno = 5;
		ft_puterror();
	}
	close(fd);
	return (0);
}

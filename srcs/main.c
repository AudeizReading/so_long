#include "../includes/so_long.h"

typedef struct	s_error
{
	int		num;
	char	*message;
	t_bool	must_exit;
}				t_error;

void	ft_puterror(void)
{
	ft_putendl_fd("Error", 2);
}

void	ft_puterr(char *err, t_bool must_exit)
{
	ft_puterror();
	ft_putendl_fd(err, 2);
	if (must_exit)
		exit(EXIT_FAILURE);
}

void	ft_parse_map_error(int errnum)
{
	int		i;
	static t_error	tab_err[] = {
		{1024, "Error encountered while reading map's lines", e_true},
		{1025, "Not a .ber map", e_true},
		{1026, "Map is not rectangular", e_true},
		{1027, "Map is not entirely closed by walls", e_true},
		{1028, "Map contains invalid characters", e_true},
		{1029, "Map does not have any exit", e_true},
		{1030, "Map does not have any collectible", e_true},
		{1031, "Map does not have any starting position", e_true},
		{-1, NULL, e_false}
	};

	i = -1;
	while (tab_err[i++].num != -1)
	{
		if (tab_err[i].num == errnum)
			ft_puterr(tab_err[i].message, tab_err[i].must_exit);
		else
			ft_puterr(strerror(errno), e_true);
	}
}

int		main(void)
{
	int		fd;
	int		gnl;
	char	*line;

	gnl = 1;
	line = NULL;
	//fd = open("srcs/main.c", O_RDONLY);
	fd = open("main.c", O_RDONLY);
	if (fd == -1)
		ft_parse_map_error(errno);
	while (gnl > 0)
	{
		gnl = get_next_line(fd, &line);
		ft_putendl_fd(line, 1);
		free(line);
	}
	if (gnl == -1)
		ft_parse_map_error(1024);
	close(fd);
	return (0);
}

#include "../includes/so_long.h"

typedef struct	s_point
{
	int				x;
	int				y;
	struct s_point	*next;
}				t_point;

typedef struct	s_line
{
	char			*content;
	int				y;
	size_t			len;
	struct	s_line	*next;
}				t_line;

typedef struct	s_map
{
	size_t	cols;
	size_t	lines;
//	t_point	start;
//	t_point	collect;
//	t_point	end;
//	t_list	*line;
}				t_map;

t_line	*ft_init_line(char *content, int pos)
{
	t_line	*new_line;

	new_line = (t_line *)malloc(sizeof(*new_line));
	if (!new_line)
		return (NULL);
	new_line->content = ft_strdup(content);
	new_line->y = pos;
	new_line->len = ft_strlen(new_line->content);
	new_line->next = NULL;
	return (new_line);
}

int			ft_map_size(t_line *map)
{
	int			size;

	size = 0;
	while (map)
	{
		size++;
		map = map->next;
	}
	return (size);
}

t_line	*ft_last_line(t_line *map)
{
	if (!map)
		return (NULL);
	while (map->next)
		map = map->next;
	return (map);
}

void		ft_map_addback(t_line **map, t_line *line)
{
	t_line	*last_line;

	if (!*map)
	{
		(*map) = line;
		return ;
	}
	last_line = ft_last_line(*map);
	last_line->next = line;
}

void		ft_map_delone(t_line *line, void (*del)(void *))
{
	(*del)(line->content);
	free(line);
	line = NULL;
}

void		ft_map_clear(t_line **map, void (*del)(void *))
{
	t_line	*tmp;

	while (*map)
	{
		tmp = (*map)->next;
		ft_map_delone(*map, del);
		(*map) = tmp;
	}
}

void		ft_print_map(t_line *map)
{
	while (map)
	{
		ft_putendl_fd(map->content, 1);
		ft_putnbr_fd(map->y, 1);
		ft_putstr_fd(" pos y\n", 1);
		ft_putnbr_fd(map->len, 1);
		ft_putstr_fd(" length line\n", 1);
		map = map->next;
	}
}

int		main(int argc, char **argv)
{
	int		fd;
	int		gnl;
	char	*line;
	t_map	*map;
	t_line	*m_line;
	t_line	*m_tmp;
	int		y;

	gnl = 1;
	y = 0;
	line = NULL;
	m_line = NULL;
	map  = &(t_map){0, 0, /*{0, 0}, {0, 0}*/};
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			ft_parse_map_error(errno);
		if (!ft_is_map_file(argv[1], ".ber"))
			ft_parse_map_error(79);
		while (gnl > 0)
		{
			gnl = get_next_line(fd, &line);
		//	ft_putendl_fd(line, 1);
			if (gnl)
			{
				m_tmp = ft_init_line(line, y++);
				//y++;
				ft_map_addback(&m_line, m_tmp);
			}
			free(line);
		}
		if (gnl == -1)
			ft_parse_map_error(errno);
	/*	ft_putendl_fd("------MAP------------------------", 1);
		ft_print_list(map_line);
		ft_putendl_fd("---------------------------------", 1);
		ft_putnbr_fd(ft_lstsize(map_line), 1);
		ft_putendl_fd(" maillons", 1);*/
		ft_putendl_fd("------MY_MAP---------------------", 1);
		ft_print_map(m_line);
		ft_putendl_fd("---------------------------------", 1);
		ft_putnbr_fd(ft_map_size(m_line), 1);
		ft_putendl_fd(" maillons", 1);
//		ft_lstclear(&map_line, free);
		ft_map_clear(&m_line, free);
		close(fd);
	}
	else
		ft_parse_map_error(22);
	return (0);
}

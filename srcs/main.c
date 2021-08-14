#include "../includes/so_long.h"

typedef struct	s_point
{
	int				x;
	int				y;
	int				pos;
	struct s_point	*next;
}				t_point;

typedef struct	s_map
{
	size_t	cols;
	size_t	lines;
//	t_point	*start;
//	t_point	*collect;
//	t_point	*end;
	t_line	*first_line;
}				t_map;

t_point	*ft_init_point(int x, int y, int pos)
{
	t_point	*point;

	point = (t_point *)malloc(sizeof(*point));
	if (!point)
		return (NULL);
	point->x = x;
	point->y = y;
	point->pos = pos;
	point->next = NULL;
	return (point);
}

int		ft_point_list_size(t_point *point)
{
	int		size;

	size = 0;
	while (point)
	{
		size++;
		point = point->next;
	}
	return (size);
}

t_point	*ft_last_point(t_point *point)
{
	if (!point)
		return (NULL);
	while (point->next)
		point = point->next;
	return (point);
}

void	ft_point_addback(t_point **point, t_point *last_point)
{
	t_point	*last;

	if (!*point)
	{
		*point = last_point;
		return ;
	}
	last = ft_last_point(*point);
	last->next = last_point;
}

void	ft_point_clear(t_point **point, void (*del)(void *))
{
	t_point	*tmp;

	while (*point)
	{
		tmp = *point->next;
		(*del)(*point);
		(*point) = tmp;
	}
}

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

	map  = &(t_map){0, 0, /*{0, 0}, {0, 0}*/NULL};
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			ft_parse_map_error(errno);
		if (!ft_is_map_file(argv[1], ".ber"))
			ft_parse_map_error(79);
		map->first_line = ft_get_map(fd);
		map->lines = ft_map_size(map->first_line);
		map->cols = map->first_line->len;
		print_info_map(map);
		ft_map_clear(&map->first_line, free);
		close(fd);
	}
	else
		ft_parse_map_error(22);
	return (0);
}

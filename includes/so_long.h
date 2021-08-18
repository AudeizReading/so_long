#ifndef SO_LONG_H
# define SO_LONG_H
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "../lib/libft/libft.h"
# include "../lib/gnl/get_next_line.h"

typedef struct	s_error
{
	int		num;
	char	*message;
	t_bool	must_exit;
}				t_error;

typedef struct	s_line
{
	char			*content;
	int				y;
	size_t			len;
	struct	s_line	*next;
}				t_line;

typedef struct	s_point
{
	int				x;
	int				y;
	int				pos;
	struct s_point	*next;
}				t_point;

void	ft_puterror(void);
void	ft_puterr(char *err, t_bool must_exit);
void	ft_parse_map_error(int errnum);
t_bool	ft_is_map_file(char *filename, char *ext);
t_line	*ft_init_line(char *content, int pos);
int		ft_map_size(t_line *map);
t_line	*ft_last_line(t_line *map);
void	ft_map_addback(t_line **map, t_line *line);
void	ft_map_delone(t_line *line, void (*del)(void *));
void	ft_map_clear(t_line **map, void (*del)(void *));
void	ft_print_map(t_line *map);
void	ft_check_line(t_line *tmp, t_line **map);
void	ft_set_map(int gnl, char *line, int *y, t_line **map);
t_line	*ft_get_map(int fd);
t_point	*ft_init_point(int x, int y, int pos);
t_point	*ft_last_point(t_point *point);
int		ft_point_list_size(t_point *point);
void	ft_point_addback(t_point **point, t_point *last_point);
void	ft_point_clear(t_point **point, void (*del)(void *));
void	ft_print_point_list(t_point *point);
//void	print_info_map(t_map *map);
int		main(int argc, char **argv);
#endif

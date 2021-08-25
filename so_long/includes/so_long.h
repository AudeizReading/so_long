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
# include "../lib/minilibx_mms_20200219/mlx.h"

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

typedef struct	s_map
{
	size_t	cols;
	size_t	lines;
	t_point	*start;
	t_point	*collect;
	t_point	*end;
	t_point	*wall;
	t_line	*first_line;
}				t_map;

typedef struct	s_img
{
	void	*def;
	void	*addr;
	int		bpp;
	int		len;
	int		end;
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	t_point	*coord;
}				t_img;

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
t_map	*ft_init_map(void);
void	print_info_map(t_map *map);
t_bool	ft_check_valid_characters(t_line *map);
t_bool	ft_check_wall(t_line *map);
t_point	*ft_has_object(t_line *line, char c, int i);
t_bool	ft_is_rectangular_map(t_line *map);
void	ft_get_objects_pos(t_map *map);
void	ft_clean_map(t_map *map);
t_map	*ft_parse_map(int fd, char **argv);
int		ft_get_trgb(int t, int r, int g, int b);
int		ft_get_t(int trgb);
int		ft_get_r(int trgb);
int		ft_get_g(int trgb);
int		ft_get_b(int trgb);
void	ft_get_img_mlx(t_img *img);
void	ft_get_img_win(t_img *img, char *title);
void	ft_get_img_def(t_img *img);
void	ft_get_img_addr(t_img *img);
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color);
void	ft_fill_screen(t_img *img, int color);
void	ft_draw_screen_grid_map(t_img *img, int color, t_map *map);
void	ft_draw_screen_grid_bpp(t_img *img, int color);
void	ft_draw_polyg(t_img *img, t_point *start, int size, int color);
int		ft_hook_close_mlx(t_img *img);
int		ft_hook_key_esc(int keycode, t_img *img);
int		main(int argc, char **argv);
#endif

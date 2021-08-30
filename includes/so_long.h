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

enum			e_color
{
	grey = 0x454545,
	blue = 0x0000AB,
	purple = 0x993366,
	//pink = 0xCF22CF,
	pink = 0xDD99DD,
	green = 0x00AB00,
	red = 0xAB0000,
	cyan = 0x00AAA9,
	//llow = 0xE6D647,
	yellow = 0xE6D677,
	ocre = 0x998D22,
	turquoise = 0x35D6E5,
	fuschia = 0xFF00FF,
	teal = 0x2B9099
};

typedef struct	s_error
{
	int				num;
	char			*message;
	t_bool			must_exit;
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
	size_t			cols;
	size_t			lines;
	t_point			*start;
	t_point			*collect;
	t_point			*end;
	t_point			*wall;
	t_line			*first_line;
}				t_map;

typedef struct	s_screen
{
	void			*mlx;
	void			*win;
	char			*title;
	unsigned int	width;
	unsigned int	height;
}				t_screen;

typedef struct	s_img
{
	void			*def;
	void			*addr;
	int				bpp;
	int				len;
	int				end;
	unsigned int	width;
	unsigned int	height;
}				t_img;

typedef struct	s_player
{
	t_point		*pole_pos;
	t_screen	*screen;
	t_img		*img;
	t_map		*map;
	int			fd;
}				t_player;

/* Errors handling */
void	ft_puterror(void);
void	ft_puterr(char *err, t_bool must_exit);
void	ft_parse_map_error(int errnum);
t_bool	ft_is_map_file(char *filename, char *ext);

/* Line of map handling */
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

/* Coordinates handling */
t_point	*ft_init_point(int x, int y, int pos);
t_point	*ft_last_point(t_point *point);
int		ft_point_list_size(t_point *point);
void	ft_point_addback(t_point **point, t_point *last_point);
void	ft_point_clear(t_point **point, void (*del)(void *));
void	ft_print_point_list(t_point *point);

/* Map .ber handling */
t_map	*ft_init_map(void);
void	print_info_map(t_map *map);
t_bool	ft_check_valid_characters(t_line *map);
t_bool	ft_check_wall(t_line *map);
t_point	*ft_has_object(t_line *line, char c, int i);
t_bool	ft_is_rectangular_map(t_line *map);
void	ft_get_objects_pos(t_map *map);
void	ft_clean_map(t_map *map);
t_map	*ft_parse_map(int fd, char **argv);

/* Colors handling */
int		ft_get_trgb(int t, int r, int g, int b);
int		ft_get_t(int trgb);
int		ft_get_r(int trgb);
int		ft_get_g(int trgb);
int		ft_get_b(int trgb);

/* Screen handling */
void	ft_get_img_mlx(t_screen *screen);
void	ft_get_img_win(t_screen *screen);

/* Image handling */
void	ft_get_img_def(t_player *player);
void	ft_get_img_addr(t_img *img);
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color);

/* Player handling */
void	ft_clean_player(t_player *player);

/* Drawing handling */
void	ft_fill_screen(t_img *img, int color);
void	ft_draw_screen_grid_map(t_img *img, int color, t_map *map);
void	ft_draw_screen_grid_bpp(t_img *img, int color);
void	ft_draw_square(t_img *img, t_point *start, int size, int color);

/* Events handling */
int		ft_hook_close_mlx(t_player *player);
int		ft_hook_key_esc(int keycode, t_player *player);

/* Starting prog */
int		main(int argc, char **argv);
#endif

#ifndef SO_LONG_H
# define SO_LONG_H
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

void	ft_puterror(void);
void	ft_puterr(char *err, t_bool must_exit);
void	ft_parse_map_error(int errnum);
int		main(void);
#endif

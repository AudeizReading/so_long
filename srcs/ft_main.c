#include <unistd.h>
#include "../lib/libft/libft.h"

/*void	ft_putstr(char *s)
{
	while (*s)
		write(1, s++, 1);
}*/

int		main(void)
{
	ft_putstr_fd("Ca fonctionne\n", 1);
	return (0);
}

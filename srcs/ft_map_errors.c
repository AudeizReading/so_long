#include "../includes/so_long.h"

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

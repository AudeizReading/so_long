#include "../includes/so_long.h"

t_bool	ft_is_map_file(char *filename, char *ext)
{
	size_t	name_len;
	size_t	ext_len;

	name_len = ft_strlen(filename);
	ext_len = ft_strlen(ext);
	if (!ft_strncmp(filename + (name_len - ext_len), ext, ext_len))
		return (e_true);
	return (e_false);
}

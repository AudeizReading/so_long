#include "../includes/so_long.h"

t_list	*ft_new_mapline(void *content)
{
	t_list	*new_map;

	new_map = (t_list *)malloc(sizeof(t_list));
	if (!new_map)
		return (NULL);
	new_map->content = ft_strdup(content);
	new_map->next = NULL;
	return (new_map);
}

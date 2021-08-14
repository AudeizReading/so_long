/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <alellouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 19:26:42 by alellouc          #+#    #+#             */
/*   Updated: 2021/08/14 19:26:46 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_line	*ft_get_map(int fd)
{
	t_line	*map;
	t_line	*tmp;
	int		gnl;
	int		y;
	char	*line;

	gnl = 1;
	y = 0;
	map = NULL;
	line = NULL;
	while (gnl > 0)
	{
		gnl = get_next_line(fd, &line);
		if (gnl)
		{
			tmp = ft_init_line(line, y++);
			ft_map_addback(&map, tmp);
		}
		free(line);
	}
	if (gnl == -1)
		ft_parse_map_error(errno);
	return (map);
}

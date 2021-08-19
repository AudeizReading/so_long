/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_objects_pos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 14:38:47 by alellouc          #+#    #+#             */
/*   Updated: 2021/08/19 14:38:57 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_get_objects_pos(t_map *map)
{
	map->start = ft_has_object(map->first_line, 'P', 0);
	if (!map->start)
		ft_parse_map_error(1032);
	map->collect = ft_has_object(map->first_line, 'C', 0);
	if (!map->collect)
		ft_parse_map_error(1031);
	map->end = ft_has_object(map->first_line, 'E', 0);
	if (!map->end)
		ft_parse_map_error(1030);
	map->wall = ft_has_object(map->first_line, '1', 0);
	if (!map->wall || !ft_check_wall(map->first_line))
		ft_parse_map_error(1028);
}

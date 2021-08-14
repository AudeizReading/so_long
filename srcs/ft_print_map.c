/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <alellouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 19:22:05 by alellouc          #+#    #+#             */
/*   Updated: 2021/08/14 19:22:15 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void		ft_print_map(t_line *map)
{
	while (map)
	{
		ft_putendl_fd(map->content, 1);
		ft_putnbr_fd(map->y, 1);
		ft_putstr_fd(" pos y\n", 1);
		ft_putnbr_fd(map->len, 1);
		ft_putstr_fd(" length line\n", 1);
		map = map->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:40:53 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/09 15:09:45 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	allocat_door(t_scene *scene, int i, int j, int *count)
{
	scene->doors[*count] = ft_calloc(1, sizeof(t_door));
	if (!scene->doors[*count])
		exit(0);
	scene->doors[*count]->pos[Y] = j;
	scene->doors[*count]->pos[X] = i;
	scene->doors[*count]->state = CLOSED;
	(*count)++;
}

void	allocat_doors(t_scene *scene)
{
	int i;
	int count;
	int j;

	scene->doors = ft_calloc(scene->door_count, sizeof(t_door *));
	if (!scene->doors)
		exit(0);
	i = -1;
	count = 0;
	while (++i < scene->map->map_height)
	{
		j = -1;
		while (++j < scene->map->map_width)
		{
			if (scene->map->map[i][j] == 'D')
				allocat_door(scene, i, j, &count);
		}
	}
}
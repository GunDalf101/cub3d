/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:12:11 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/11 19:16:23 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	allocate_sprite_memory(t_scene *scene)
{
	scene->sprites = ft_calloc(scene->sprite_count, sizeof(t_sprite *));
	if (!scene->sprites)
		exit(0);
}

void	create_and_initialize_sprites(t_scene *scene)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (++i < scene->map->map_height)
	{
		j = -1;
		while (++j < scene->map->map_width)
		{
			if (scene->map->map[i][j] == 'B')
				allocat_barrel(scene, i, j, &count);
			else if (scene->map->map[i][j] == 'P')
				allocat_pillar(scene, i, j, &count);
			else if (scene->map->map[i][j] == 'M')
				allocat_manaorb(scene, i, j, &count);
			else if (scene->map->map[i][j] == 'V')
				allocat_warlock(scene, i, j, &count);
			else if (scene->map->map[i][j] == 'Z'
				|| scene->map->map[i][j] == 'Y')
				allocat_portal(scene, i, j, &count);
		}
	}
}

void	allocat_sprites(t_scene *scene)
{
	allocate_sprite_memory(scene);
	create_and_initialize_sprites(scene);
}

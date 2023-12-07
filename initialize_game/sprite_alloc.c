/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 22:04:52 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/07 10:41:36 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	allocat_barrel(t_scene *scene, int i, int j, int *count)
{
	scene->sprites[*count] = ft_calloc(1, sizeof(t_sprite));
	if (!scene->sprites[*count])
		exit(0);
	scene->sprites[*count]->sprite_img = scene->barrel_img;
	scene->sprites[*count]->v_move = 1100 * WIN_HEIGHT / 1200;
	scene->sprites[*count]->collision_box = 40;
	scene->sprites[*count]->pos[Y] = j * UNIT + UNIT / 2;
	scene->sprites[*count]->pos[X] = i * UNIT + UNIT / 2;
	(*count)++;
}

void	allocat_pillar(t_scene *scene, int i, int j, int *count)
{
	scene->sprites[*count] = ft_calloc(1, sizeof(t_sprite));
	if (!scene->sprites[*count])
		exit(0);
	scene->sprites[*count]->sprite_img = scene->pillar_img;
	scene->sprites[*count]->v_move = 50 * WIN_HEIGHT / 1200;
	scene->sprites[*count]->collision_box = 40;
	scene->sprites[*count]->pos[Y] = j * UNIT + UNIT / 2;
	scene->sprites[*count]->pos[X] = i * UNIT + UNIT / 2;
	(*count)++;
}

void	allocat_manaorb(t_scene *scene, int i, int j, int *count)
{
	scene->sprites[*count] = ft_calloc(1, sizeof(t_sprite));
	if (!scene->sprites[*count])
		exit(0);
	scene->sprites[*count]->sprite_img = scene->manaorb_img;
	scene->sprites[*count]->v_move = -500 * WIN_HEIGHT / 1200;
	scene->sprites[*count]->collision_box = 0;
	scene->sprites[*count]->pos[Y] = j * UNIT + UNIT / 2;
	scene->sprites[*count]->pos[X] = i * UNIT + UNIT / 2;
	(*count)++;
}

void	allocat_sprites(t_scene *scene)
{
	int	i;
	int	count;
	int	j;

	scene->sprites = ft_calloc(scene->sprite_count, sizeof(t_sprite *));
	if (!scene->sprites)
		exit(0);
	i = 0;
	count = 0;
	while (i < scene->map->map_height)
	{
		j = 0;
		while (j < scene->map->map_width)
		{
			if (scene->map->map[i][j] == 'B')
				allocat_barrel(scene, i, j, &count);
			if (scene->map->map[i][j] == 'P')
				allocat_pillar(scene, i, j, &count);
			if (scene->map->map[i][j] == 'M')
				allocat_manaorb(scene, i, j, &count);
			j++;
		}
		i++;
	}
}

void	initsprites(t_scene *scene)
{
	load_sprites(scene);
	load_projectiles(scene);
	sprite_count(scene);
	allocat_sprites(scene);
}

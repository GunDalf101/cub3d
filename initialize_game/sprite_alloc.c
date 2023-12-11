/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 22:04:52 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/10 23:28:34 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"
#include <limits.h>

void	allocat_barrel(t_scene *scene, int i, int j, int *count)
{
	scene->sprites[*count] = ft_calloc(1, sizeof(t_sprite));
	if (!scene->sprites[*count])
		exit(0);
	scene->sprites[*count]->sprite_img = scene->barrel_img;
	scene->sprites[*count]->animation_img = NULL;
	scene->sprites[*count]->v_move = 1100 * WIN_HEIGHT / 1200;
	scene->sprites[*count]->collision_box = 30;
	scene->sprites[*count]->hitbox = 30;
	scene->sprites[*count]->pos[Y] = j * UNIT + UNIT / 2;
	scene->sprites[*count]->pos[X] = i * UNIT + UNIT / 2;
	scene->sprites[*count]->hitpoint = 150;
	scene->sprites[*count]->sprite_type = BARREL;
	(*count)++;
}

void	allocat_pillar(t_scene *scene, int i, int j, int *count)
{
	scene->sprites[*count] = ft_calloc(1, sizeof(t_sprite));
	if (!scene->sprites[*count])
		exit(0);
	scene->sprites[*count]->sprite_img = scene->pillar_img;
	scene->sprites[*count]->animation_img = NULL;
	scene->sprites[*count]->v_move = 50 * WIN_HEIGHT / 1200;
	scene->sprites[*count]->collision_box = 30;
	scene->sprites[*count]->hitbox = 20;
	scene->sprites[*count]->pos[Y] = j * UNIT + UNIT / 2;
	scene->sprites[*count]->pos[X] = i * UNIT + UNIT / 2;
	scene->sprites[*count]->hitpoint = 500;
	scene->sprites[*count]->sprite_type = PILLAR;
	(*count)++;
}

void	allocat_manaorb(t_scene *scene, int i, int j, int *count)
{
	scene->sprites[*count] = ft_calloc(1, sizeof(t_sprite));
	if (!scene->sprites[*count])
		exit(0);
	scene->sprites[*count]->sprite_img = scene->manaorb_img;
	scene->sprites[*count]->animation_img = NULL;
	scene->sprites[*count]->v_move = -500 * WIN_HEIGHT / 1200;
	scene->sprites[*count]->collision_box = 0;
	scene->sprites[*count]->hitbox = 0;
	scene->sprites[*count]->pos[Y] = j * UNIT + UNIT / 2;
	scene->sprites[*count]->pos[X] = i * UNIT + UNIT / 2;
	scene->sprites[*count]->hitpoint = INT_MAX;
	scene->sprites[*count]->sprite_type = MANAORB;
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
	i = -1;
	count = 0;
	while (++i < scene->map->map_height)
	{
		j = -1;
		while (++j < scene->map->map_width)
		{
			if (scene->map->map[i][j] == 'B')
				allocat_barrel(scene, i, j, &count);
			if (scene->map->map[i][j] == 'P')
				allocat_pillar(scene, i, j, &count);
			if (scene->map->map[i][j] == 'M')
				allocat_manaorb(scene, i, j, &count);
			if (scene->map->map[i][j] == 'V')
				allocat_warlock(scene, i, j, &count);
		}
	}
}

void	initsprites(t_scene *scene)
{
	scene->score_img = NULL;
	scene->projectiles = NULL;
	scene->win = FALSE;
	scene->timer.time_origin = mlx_get_time();
	load_sprites(scene);
	load_projectiles(scene);
	load_warlock(scene->mlx_ptr, scene);
	load_end(scene);
	load_floor_textures(scene);
	sprite_count(scene);
	allocat_sprites(scene);
	allocat_doors(scene);
}

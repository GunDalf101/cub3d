/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 22:04:52 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/15 10:54:13 by mbennani         ###   ########.fr       */
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
	scene->sprites[*count]->state = IDLE;
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
	scene->sprites[*count]->state = IDLE;
	(*count)++;
}

void	allocat_portal(t_scene *scene, int i, int j, int *count)
{
	scene->sprites[*count] = ft_calloc(1, sizeof(t_sprite));
	if (!scene->sprites[*count])
		exit(0);
	scene->sprites[*count]->sprite_img = scene->portal_img;
	scene->sprites[*count]->animation_img = NULL;
	scene->sprites[*count]->v_move = -500 * WIN_HEIGHT / 1200;
	scene->sprites[*count]->collision_box = 0;
	scene->sprites[*count]->hitbox = 0;
	scene->sprites[*count]->pos[Y] = j * UNIT + UNIT / 2;
	scene->sprites[*count]->pos[X] = i * UNIT + UNIT / 2;
	scene->sprites[*count]->hitpoint = INT_MAX;
	scene->sprites[*count]->sprite_type = PORTAL;
	scene->sprites[*count]->state = IDLE;
	(*count)++;
}

void	initsprites(t_scene *scene)
{
	scene->score_img = NULL;
	scene->projectiles = NULL;
	scene->win = FALSE;
	scene->fast_travel = FALSE;
	scene->light_multiplier = 0.5;
	scene->z_buffer = malloc(sizeof(double) * WIN_WIDTH);
	scene->timer.time_origin = mlx_get_time();
	load_sprites(scene);
	load_projectiles(scene);
	load_warlock(scene->mlx_ptr, scene);
	load_sword(scene->mlx_ptr, scene);
	load_end(scene);
	load_floor_textures(scene);
	sprite_count(scene);
	allocat_sprites(scene);
	allocat_doors(scene);
}

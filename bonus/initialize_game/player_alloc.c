/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:50:00 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/15 10:54:51 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	allocat_warlock(t_scene *scene, int i, int j, int *count)
{
	scene->sprites[*count] = ft_calloc(1, sizeof(t_sprite));
	if (!scene->sprites[*count])
		exit(0);
	scene->sprites[*count]->animation_img = scene->evil_warlock[0];
	scene->sprites[*count]->v_move = 500 * WIN_HEIGHT / 1200;
	scene->sprites[*count]->collision_box = 0;
	scene->sprites[*count]->hitbox = 30;
	scene->sprites[*count]->pos[Y] = j * UNIT + UNIT / 2;
	scene->sprites[*count]->pos[X] = i * UNIT + UNIT / 2;
	scene->sprites[*count]->hitpoint = 100;
	scene->sprites[*count]->sprite_type = WARLOCK;
	scene->sprites[*count]->state = IDLE;
	scene->sprites[*count]->dir[Y] = 0;
	scene->sprites[*count]->dir[X] = 0;
	scene->sprites[*count]->sped = 100;
	(*count)++;
}

void	player_dir(t_scene *scene, int i, int j)
{
	if (scene->map->map[i][j] == 'N')
	{
		scene->player->pos[Y] = j * UNIT + UNIT / 2;
		scene->player->pos[X] = i * UNIT + UNIT / 2;
		scene->player->p_angle = -M_PI_2;
	}
	else if (scene->map->map[i][j] == 'S')
	{
		scene->player->pos[Y] = j * UNIT + UNIT / 2;
		scene->player->pos[X] = i * UNIT + UNIT / 2;
		scene->player->p_angle = M_PI_2;
	}
	else if (scene->map->map[i][j] == 'E')
	{
		scene->player->pos[Y] = j * UNIT + UNIT / 2;
		scene->player->pos[X] = i * UNIT + UNIT / 2;
		scene->player->p_angle = 0;
	}
	else if (scene->map->map[i][j] == 'W')
	{
		scene->player->pos[Y] = j * UNIT + UNIT / 2;
		scene->player->pos[X] = i * UNIT + UNIT / 2;
		scene->player->p_angle = M_PI;
	}
}

void	initialize_player(t_scene *scene)
{
	scene->player->dir[Y] = (double)cos(scene->player->p_angle) * 25;
	scene->player->dir[X] = (double)sin(scene->player->p_angle) * 25;
	scene->player->plane[Y] = (double)cos(scene->player->p_angle + M_PI / 2)
		* 16.5;
	scene->player->plane[X] = (double)sin(scene->player->p_angle + M_PI / 2)
		* 16.5;
	scene->player->health_points = UNIT;
	scene->player->mana_points = UNIT;
	scene->player->central_angle = 0;
	scene->player->is_ded = FALSE;
	scene->player->forward = FALSE;
	scene->player->rot_left = FALSE;
	scene->player->rot_right = FALSE;
	scene->player->backwards = FALSE;
	scene->player->left = FALSE;
	scene->player->right = FALSE;
	scene->player->velocity = 2;
	scene->player->is_jumping = FALSE;
	scene->player->is_trapped = FALSE;
	scene->player->is_lit = FALSE;
	scene->player->crouch = FALSE;
	scene->player->will_collide[Y] = FALSE;
	scene->player->will_collide[X] = FALSE;
}

void	allocat_player(t_scene *scene)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	scene->score = 0;
	scene->player = malloc(sizeof(t_player));
	if (!scene->player)
		exit(0);
	while (i < scene->map->map_height)
	{
		j = 0;
		while (j < scene->map->map_width)
		{
			player_dir(scene, i, j);
			j++;
		}
		i++;
	}
	scene->player->attacking = FALSE;
	initialize_player(scene);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:50:00 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/13 19:58:14 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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
	scene->player->dir[Y] = (double)cosf(scene->player->p_angle) * 25;
	scene->player->dir[X] = (double)sinf(scene->player->p_angle) * 25;
	scene->player->plane[Y] = (double)cosf(scene->player->p_angle + M_PI / 2)
		* 16.5;
	scene->player->plane[X] = (double)sinf(scene->player->p_angle + M_PI / 2)
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
	scene->player->velocity = 1.5;
	scene->player->is_jumping = FALSE;
	scene->player->is_trapped = FALSE;
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

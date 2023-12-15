/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:08:43 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/15 10:57:36 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	idle(t_scene *scene, int i)
{
	scene->sprites[i]->dir[X] = 0;
	scene->sprites[i]->dir[Y] = 0;
}

void	pursuit(t_scene *scene, int i)
{
	scene->sprites[i]->dir[X] = scene->player->pos[X]
		- scene->sprites[i]->pos[X];
	scene->sprites[i]->dir[Y] = scene->player->pos[Y]
		- scene->sprites[i]->pos[Y];
	scene->sprites[i]->dir[X] /= scene->sprites[i]->sprite_distance;
	scene->sprites[i]->dir[Y] /= scene->sprites[i]->sprite_distance;
	scene->sprites[i]->pos[X] += scene->sprites[i]->dir[X]
		* scene->sprites[i]->sped * scene->frame_time;
	scene->sprites[i]->pos[Y] += scene->sprites[i]->dir[Y]
		* scene->sprites[i]->sped * scene->frame_time;
}

void	attack(t_scene *scene, int i)
{
	static double	frame;
	t_dda			dda;

	dda.x1 = scene->player->pos[X];
	dda.y1 = scene->player->pos[Y];
	if (line_o_sight(dda, scene->sprites[i]->pos[X], scene->sprites[i]->pos[Y],
			*scene))
		pursuit(scene, i);
	if (scene->sprites[i]->sprite_distance < 100 && (int)frame % 10 == 0)
		scene->player->health_points -= 5;
	frame += 0.7 / scene->move_speed;
}

void	state_machine(t_scene *scene, int i)
{
	if (scene->sprites[i]->sprite_type == WARLOCK)
	{
		if (scene->sprites[i]->state == IDLE)
			idle(scene, i);
		else if (scene->sprites[i]->state == PURSUIT)
			pursuit(scene, i);
		else if (scene->sprites[i]->state == ATTACK)
			attack(scene, i);
	}
}

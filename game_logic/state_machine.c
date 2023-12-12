/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:08:43 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/12 22:45:58 by mbennani         ###   ########.fr       */
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
		* scene->sprites[i]->sped;
	scene->sprites[i]->pos[Y] += scene->sprites[i]->dir[Y]
		* scene->sprites[i]->sped;
}

void	attack(t_scene *scene, int i)
{
	static int	frame;
	t_dda		dda;

	dda.x1 = scene->player->pos[X];
	dda.y1 = scene->player->pos[Y];
	if (line_o_sight(dda, scene->sprites[i]->pos[X], scene->sprites[i]->pos[Y],
			*scene))
		pursuit(scene, i);
	if (scene->sprites[i]->sprite_distance < 100 && frame % 10 == 0)
		scene->player->health_points -= 5;
	frame++;
}

void	state_machine(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->sprite_count)
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
		i++;
	}
}

// void	check_enemy_state(t_scene *scene)
// {
// 	int		i;
// 	t_dda	dda;

// 	i = 0;
// 	dda.x1 = scene->player->pos[X];
// 	dda.y1 = scene->player->pos[Y];
// 	while (i < scene->sprite_count)
// 	{
// 		if (scene->sprites[i]->sprite_type == WARLOCK
// 			&& scene->sprites[i]->state != DEAD)
// 		{
// 			scene->war_index = i;
// 			if (scene->player->pos[X] + 50 > scene->sprites[i]->pos[X]
// 				&& scene->player->pos[X] - 50 < scene->sprites[i]->pos[X]
// 				&& scene->player->pos[Y] + 50 > scene->sprites[i]->pos[Y]
// 				&& scene->player->pos[Y] - 50 < scene->sprites[i]->pos[Y])
// 				scene->sprites[i]->state = ATTACK;
// 			else if (scene->player->pos[X] + 10
// 				* UNIT > scene->sprites[i]->pos[X] && scene->player->pos[X] - 10
// 				* UNIT < scene->sprites[i]->pos[X] && scene->player->pos[Y] + 10
// 				* UNIT > scene->sprites[i]->pos[Y] && scene->player->pos[Y] - 10
// 				* UNIT < scene->sprites[i]->pos[Y] && line_o_sight(dda,
// 					scene->sprites[i]->pos[X], scene->sprites[i]->pos[Y],
// 					*scene))
// 				scene->sprites[i]->state = PURSUIT;
// 			else
// 				scene->sprites[i]->state = IDLE;
// 		}
// 		i++;
// 	}
// }

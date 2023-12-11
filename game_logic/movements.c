/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:35:24 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/09 19:23:32 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	move_forward(t_scene *scene)
{
	if (scene->map->map[(int)(scene->player->pos[X])
		/ UNIT][(int)(scene->player->pos[Y] + scene->player->dir[Y] * 2
			* scene->move_speed) / (UNIT)] != '1' && !does_it_collide(scene, 1)
		&& (scene->map->map[(int)(scene->player->pos[X])
			/ UNIT][(int)(scene->player->pos[Y] + scene->player->dir[Y] * 2
				* scene->move_speed) / (UNIT)] != 'D'))
		scene->player->pos[Y] += scene->player->dir[Y] * scene->move_speed;
	if (scene->map->map[(int)(scene->player->pos[X] + scene->player->dir[X] * 2
			* scene->move_speed) / (UNIT)][(int)(scene->player->pos[Y])
		/ UNIT] != '1' && !does_it_collide(scene, 2)
		&& (scene->map->map[(int)(scene->player->pos[X] + scene->player->dir[X]
				* 2 * scene->move_speed) / (UNIT)][(int)(scene->player->pos[Y])
			/ UNIT] != 'D'))
		scene->player->pos[X] += scene->player->dir[X] * scene->move_speed;
}

void	move_backward(t_scene *scene)
{
	if (scene->map->map[(int)(scene->player->pos[X])
		/ UNIT][(int)(scene->player->pos[Y] - scene->player->dir[Y] * 2
			* scene->move_speed) / (UNIT)] != '1' && !does_it_collide(scene, 3)
		&& (scene->map->map[(int)(scene->player->pos[X])
			/ UNIT][(int)(scene->player->pos[Y] - scene->player->dir[Y] * 2
				* scene->move_speed) / (UNIT)] != 'D'))
		scene->player->pos[Y] -= scene->player->dir[Y] * scene->move_speed;
	if (scene->map->map[(int)(scene->player->pos[X] - scene->player->dir[X] * 2
			* scene->move_speed) / (UNIT)][(int)(scene->player->pos[Y])
		/ UNIT] != '1' && !does_it_collide(scene, 4)
		&& (scene->map->map[(int)(scene->player->pos[X] - scene->player->dir[X]
				* 2 * scene->move_speed) / (UNIT)][(int)(scene->player->pos[Y])
			/ UNIT] != 'D'))
		scene->player->pos[X] -= scene->player->dir[X] * scene->move_speed;
}

void	move_left(t_scene *scene)
{
	if (scene->map->map[(int)(scene->player->pos[X])
		/ UNIT][(int)(scene->player->pos[Y] - scene->player->plane[Y] * 2
			* scene->move_speed) / (UNIT)] != '1' && !does_it_collide(scene, 5)
		&& (scene->map->map[(int)(scene->player->pos[X])
			/ UNIT][(int)(scene->player->pos[Y] - scene->player->plane[Y] * 2
				* scene->move_speed) / (UNIT)] != 'D'))
		scene->player->pos[Y] -= scene->player->plane[Y] * scene->move_speed;
	if (scene->map->map[(int)(scene->player->pos[X] - scene->player->plane[X]
			* 2 * scene->move_speed) / (UNIT)][(int)(scene->player->pos[Y])
		/ UNIT] != '1' && !does_it_collide(scene, 6)
		&& (scene->map->map[(int)(scene->player->pos[X]
				- scene->player->plane[X] * 2 * scene->move_speed)
			/ (UNIT)][(int)(scene->player->pos[Y]) / UNIT] != 'D'))
		scene->player->pos[X] -= scene->player->plane[X] * scene->move_speed;
}

void	move_right(t_scene *scene)
{
	if (scene->map->map[(int)(scene->player->pos[X])
		/ UNIT][(int)(scene->player->pos[Y] + scene->player->plane[Y] * 2
			* scene->move_speed) / (UNIT)] != '1' && !does_it_collide(scene, 7)
		&& (scene->map->map[(int)(scene->player->pos[X])
			/ UNIT][(int)(scene->player->pos[Y] + scene->player->plane[Y] * 2
				* scene->move_speed) / (UNIT)] != 'D'))
		scene->player->pos[Y] += scene->player->plane[Y] * scene->move_speed;
	if (scene->map->map[(int)(scene->player->pos[X] + scene->player->plane[X]
			* 2 * scene->move_speed) / (UNIT)][(int)(scene->player->pos[Y])
		/ UNIT] != '1' && !does_it_collide(scene, 8)
		&& (scene->map->map[(int)(scene->player->pos[X]
				+ scene->player->plane[X] * 2 * scene->move_speed)
			/ (UNIT)][(int)(scene->player->pos[Y]) / UNIT] != 'D'))
		scene->player->pos[X] += scene->player->plane[X] * scene->move_speed;
}

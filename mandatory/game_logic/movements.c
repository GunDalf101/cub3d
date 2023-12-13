/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:35:24 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/13 05:19:06 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	move_forward(t_scene *scene)
{
	if (scene->map->map[(int)(scene->player->pos[X])
		/ UNIT][(int)(scene->player->pos[Y] + scene->player->dir[Y] * 2
			* scene->move_speed) / (UNIT)] != '1')
		scene->player->pos[Y] += scene->player->dir[Y] * scene->move_speed;
	if (scene->map->map[(int)(scene->player->pos[X] + scene->player->dir[X] * 2
			* scene->move_speed) / (UNIT)][(int)(scene->player->pos[Y])
		/ UNIT] != '1')
		scene->player->pos[X] += scene->player->dir[X] * scene->move_speed;
}

void	move_backward(t_scene *scene)
{
	if (scene->map->map[(int)(scene->player->pos[X])
		/ UNIT][(int)(scene->player->pos[Y] - scene->player->dir[Y] * 2
			* scene->move_speed) / (UNIT)] != '1')
		scene->player->pos[Y] -= scene->player->dir[Y] * scene->move_speed;
	if (scene->map->map[(int)(scene->player->pos[X] - scene->player->dir[X] * 2
			* scene->move_speed) / (UNIT)][(int)(scene->player->pos[Y])
		/ UNIT] != '1')
		scene->player->pos[X] -= scene->player->dir[X] * scene->move_speed;
}

void	move_left(t_scene *scene)
{
	if (scene->map->map[(int)(scene->player->pos[X])
		/ UNIT][(int)(scene->player->pos[Y] - scene->player->plane[Y] * 2
			* scene->move_speed) / (UNIT)] != '1')
		scene->player->pos[Y] -= scene->player->plane[Y] * scene->move_speed;
	if (scene->map->map[(int)(scene->player->pos[X] - scene->player->plane[X]
			* 2 * scene->move_speed) / (UNIT)][(int)(scene->player->pos[Y])
		/ UNIT] != '1')
		scene->player->pos[X] -= scene->player->plane[X] * scene->move_speed;
}

void	move_right(t_scene *scene)
{
	if (scene->map->map[(int)(scene->player->pos[X])
		/ UNIT][(int)(scene->player->pos[Y] + scene->player->plane[Y] * 2
			* scene->move_speed) / (UNIT)] != '1')
		scene->player->pos[Y] += scene->player->plane[Y] * scene->move_speed;
	if (scene->map->map[(int)(scene->player->pos[X] + scene->player->plane[X]
			* 2 * scene->move_speed) / (UNIT)][(int)(scene->player->pos[Y])
		/ UNIT] != '1')
		scene->player->pos[X] += scene->player->plane[X] * scene->move_speed;
}

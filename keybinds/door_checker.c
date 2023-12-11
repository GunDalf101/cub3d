/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:26:02 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/10 23:38:49 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	open_or_closed(t_scene *scene, int door_x, int door_y, int i)
{
	if (scene->doors[i]->state == CLOSED)
	{
		scene->map->map[(int)(door_x / UNIT)][(int)(door_y / UNIT)] = 'C';
		system("afplay assets/opendoor.mp3 &");
		scene->doors[i]->state = OPEN;
	}
	else if (scene->doors[i]->state == OPEN && ((int)(scene->player->pos[X]
			/ UNIT) != (int)(door_x / UNIT) || (int)(scene->player->pos[Y]
			/ UNIT) != (int)(door_y / UNIT)))
	{
		scene->map->map[scene->doors[i]->pos[X]][scene->doors[i]->pos[Y]] = 'D';
		system("afplay assets/closedoor.mp3 &");
		scene->doors[i]->state = CLOSED;
	}
}

void	check_door(mlx_key_data_t keycode, t_scene *scene)
{
	int		i;
	double	x;
	double	y;
	double	door_x;
	double	door_y;

	(void)keycode;
	i = 0;
	x = scene->player->pos[X] + scene->player->dir[X] * 2;
	y = scene->player->pos[Y] + scene->player->dir[Y] * 2;
	while (i < scene->door_count)
	{
		door_x = scene->doors[i]->pos[X] * UNIT;
		door_y = scene->doors[i]->pos[Y] * UNIT;
		if (x <= door_x + UNIT && x >= door_x && y <= door_y + UNIT
			&& y >= door_y)
			open_or_closed(scene, door_x, door_y, i);
		i++;
	}
}

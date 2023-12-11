/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_teleport.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:08:04 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/11 19:09:39 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	check_pole(t_scene *scene)
{
	if (scene->map->map[(int)(scene->player->pos[X])
		/ UNIT][(int)(scene->player->pos[Y]) / UNIT] == 'Z'
		&& !scene->fast_travel)
	{
		scene->player->pos[X] = scene->south_pole[X] * UNIT + UNIT / 2;
		scene->player->pos[Y] = scene->south_pole[Y] * UNIT + UNIT / 2;
		system("afplay assets/teleport.mp3 &");
		usleep(800000);
		scene->fast_travel = TRUE;
	}
	if (scene->map->map[(int)(scene->player->pos[X])
		/ UNIT][(int)(scene->player->pos[Y]) / UNIT] == 'Y'
		&& !scene->fast_travel)
	{
		scene->player->pos[X] = scene->north_pole[X] * UNIT + UNIT / 2;
		scene->player->pos[Y] = scene->north_pole[Y] * UNIT + UNIT / 2;
		system("afplay assets/teleport.mp3 &");
		usleep(800000);
		scene->fast_travel = TRUE;
	}
	if (scene->map->map[(int)(scene->player->pos[X])
		/ UNIT][(int)(scene->player->pos[Y]) / UNIT] != 'Z'
		&& scene->map->map[(int)(scene->player->pos[X])
		/ UNIT][(int)(scene->player->pos[Y]) / UNIT] != 'Y')
		scene->fast_travel = FALSE;
}

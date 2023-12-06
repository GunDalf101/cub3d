/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_calcul.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:00:51 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/06 23:01:13 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	initial_calculation(t_scene *scene, int count)
{
	scene->sprites[count]->relative_pos[Y] = scene->sprites[count]->pos[Y]
		- scene->player->pos[Y];
	scene->sprites[count]->relative_pos[X] = scene->sprites[count]->pos[X]
		- scene->player->pos[X];
	scene->sprites[count]->inverse_det = 1.0 / (scene->player->plane[Y]
			* scene->player->dir[X] - scene->player->dir[Y]
			* scene->player->plane[X]);
	scene->sprites[count]->transform[Y] = scene->sprites[count]->inverse_det
		* (-scene->player->plane[X] * scene->sprites[count]->relative_pos[Y]
			+ scene->player->plane[Y] * scene->sprites[count]->relative_pos[X]);
	scene->sprites[count]->transform[X] = scene->sprites[count]->inverse_det
		* (scene->player->dir[X] * scene->sprites[count]->relative_pos[Y]
			- scene->player->dir[Y] * scene->sprites[count]->relative_pos[X]);
	scene->sprites[count]->v_move_screen = (int)(scene->sprites[count]->v_move
			/ scene->sprites[count]->transform[Y]);
	scene->sprites[count]->sprite_screen_x = (int)((WIN_WIDTH / 2) * (1
				+ scene->sprites[count]->transform[X]
				/ scene->sprites[count]->transform[Y]));
	scene->sprites[count]->sprite_height = abs((int)(scene->sprites[count]->\
		sprite_img->height / (scene->sprites[count]->transform[Y]) * 7));
}

void	line_coordinates(t_scene *scene, int count)
{
	scene->sprites[count]->start[Y] = -scene->sprites[count]->sprite_height / 2
		+ WIN_HEIGHT / 2 + scene->sprites[count]->v_move_screen;
	if (scene->sprites[count]->start[Y] < -scene->player->central_angle
		+ scene->player->crouch)
		scene->sprites[count]->start[Y] = -scene->player->central_angle
			+ scene->player->crouch;
	scene->sprites[count]->end[Y] = scene->sprites[count]->sprite_height / 2
		+ WIN_HEIGHT / 2 + scene->sprites[count]->v_move_screen;
	if (scene->sprites[count]->end[Y] >= WIN_HEIGHT
		- scene->player->central_angle + scene->player->crouch)
		scene->sprites[count]->end[Y] = WIN_HEIGHT
			- scene->player->central_angle + scene->player->crouch - 1;
	scene->sprites[count]->sprite_width = abs((int)(scene->sprites[count]->\
		sprite_img->width / (scene->sprites[count]->transform[Y]) * 7));
	scene->sprites[count]->start[X] = scene->sprites[count]->sprite_screen_x
		- scene->sprites[count]->sprite_width / 2;
	if (scene->sprites[count]->start[X] < 0)
		scene->sprites[count]->start[X] = 0;
	scene->sprites[count]->end[X] = scene->sprites[count]->sprite_screen_x
		+ scene->sprites[count]->sprite_width / 2;
	if (scene->sprites[count]->end[X] >= WIN_WIDTH)
		scene->sprites[count]->end[X] = WIN_WIDTH - 1;
}

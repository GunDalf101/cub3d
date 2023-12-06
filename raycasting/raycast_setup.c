/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:03:29 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/06 23:03:45 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	set_step_x(t_scene *scene, t_ray_caster *wizard)
{
	if (scene->player->vision_rays[wizard->x]->dir[X] < 0)
	{
		scene->player->vision_rays[wizard->x]->step[X] = -1;
		scene->player->vision_rays[wizard->x]->side_cell[X] = (scene->\
		player->vision_rays[wizard->x]->pos[X]
				- scene->player->vision_rays[wizard->x]->current_cell[X])
			* scene->player->vision_rays[wizard->x]->delta_ray[X];
	}
	else
	{
		scene->player->vision_rays[wizard->x]->step[X] = 1;
		scene->player->vision_rays[wizard->x]->side_cell[X] = (scene->\
		player->vision_rays[wizard->x]->current_cell[X]
				+ 1.0 - scene->player->vision_rays[wizard->x]->pos[X])
			* scene->player->vision_rays[wizard->x]->delta_ray[X];
	}
}

void	set_step_y(t_scene *scene, t_ray_caster *wizard)
{
	if (scene->player->vision_rays[wizard->x]->dir[Y] < 0)
	{
		scene->player->vision_rays[wizard->x]->step[Y] = -1;
		scene->player->vision_rays[wizard->x]->side_cell[Y] = (scene->\
		player->vision_rays[wizard->x]->pos[Y]
				- scene->player->vision_rays[wizard->x]->current_cell[Y])
			* scene->player->vision_rays[wizard->x]->delta_ray[Y];
	}
	else
	{
		scene->player->vision_rays[wizard->x]->step[Y] = 1;
		scene->player->vision_rays[wizard->x]->side_cell[Y] = (scene->\
		player->vision_rays[wizard->x]->current_cell[Y]
				+ 1.0 - scene->player->vision_rays[wizard->x]->pos[Y])
			* scene->player->vision_rays[wizard->x]->delta_ray[Y];
	}
}

void	set_difference(t_scene *scene, t_ray_caster *wizard)
{
	if (scene->player->vision_rays[wizard->x]->dir[Y] != 0)
		scene->player->vision_rays[wizard->x]->delta_ray[Y] = fabs(1
				/ scene->player->vision_rays[wizard->x]->dir[Y]);
	else
		scene->player->vision_rays[wizard->x]->delta_ray[Y] = __DBL_MAX__;
	if (scene->player->vision_rays[wizard->x]->dir[X] != 0)
		scene->player->vision_rays[wizard->x]->delta_ray[X] = fabs(1
				/ scene->player->vision_rays[wizard->x]->dir[X]);
	else
		scene->player->vision_rays[wizard->x]->delta_ray[X] = __DBL_MAX__;
}

void	setup_rays(t_scene *scene, t_ray_caster *wizard)
{
	scene->camera_x = 2 * wizard->x / (double)WIN_WIDTH - 1;
	scene->player->vision_rays[wizard->x] = malloc(sizeof(t_ray));
	scene->player->vision_rays[wizard->x]->will_hit = FALSE;
	scene->player->vision_rays[wizard->x]->pos[Y] = scene->player->pos[Y];
	scene->player->vision_rays[wizard->x]->pos[X] = scene->player->pos[X];
	scene->player->vision_rays[wizard->x]->dir[Y] = scene->player->dir[Y]
		+ scene->player->plane[Y] * scene->camera_x;
	scene->player->vision_rays[wizard->x]->dir[X] = scene->player->dir[X]
		+ scene->player->plane[X] * scene->camera_x;
	scene->player->vision_rays[wizard->x]->current_cell[Y] = \
	(int)scene->player->vision_rays[wizard->x]->pos[Y];
	scene->player->vision_rays[wizard->x]->current_cell[X] = \
	(int)scene->player->vision_rays[wizard->x]->pos[X];
	set_difference(scene, wizard);
	set_step_y(scene, wizard);
	set_step_x(scene, wizard);
}

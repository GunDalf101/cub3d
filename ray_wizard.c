/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_wizard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:08:25 by mbennani          #+#    #+#             */
/*   Updated: 2023/11/24 18:40:49 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ray_caster(t_scene *scene)
{
	int		x;
	x = 0;
	scene->player->vision_rays = malloc(sizeof(t_ray) * WIN_WIDTH);
	scene->z_buffer = malloc(sizeof(double) * WIN_WIDTH);
	while (x < WIN_WIDTH)
	{
		scene->camera_x = 2 * x / (double)WIN_WIDTH - 1;
		scene->player->vision_rays[x] = malloc(sizeof(t_ray));
		scene->player->vision_rays[x]->will_hit = FALSE;
		scene->player->vision_rays[x]->pos[Y] = scene->player->pos[Y];
		scene->player->vision_rays[x]->pos[X] = scene->player->pos[X];
		scene->player->vision_rays[x]->dir[Y] = scene->player->dir[Y] + scene->player->plane[Y] * scene->camera_x;
		scene->player->vision_rays[x]->dir[X] = scene->player->dir[X] + scene->player->plane[X] * scene->camera_x;
		scene->player->vision_rays[x]->current_cell[Y] = (int)scene->player->vision_rays[x]->pos[Y];
		scene->player->vision_rays[x]->current_cell[X] = (int)scene->player->vision_rays[x]->pos[X];
		if (scene->player->vision_rays[x]->dir[Y] != 0)
			scene->player->vision_rays[x]->delta_ray[Y] = fabs(1 / scene->player->vision_rays[x]->dir[Y]);
		else
			scene->player->vision_rays[x]->delta_ray[Y] = __DBL_MAX__;
		if (scene->player->vision_rays[x]->dir[X] != 0)
			scene->player->vision_rays[x]->delta_ray[X] = fabs(1 / scene->player->vision_rays[x]->dir[X]);
		else
			scene->player->vision_rays[x]->delta_ray[X] = __DBL_MAX__;
		if (scene->player->vision_rays[x]->dir[Y] < 0)
		{
			scene->player->vision_rays[x]->step[Y] = -1;
			scene->player->vision_rays[x]->side_cell[Y] = (scene->player->vision_rays[x]->pos[Y] - scene->player->vision_rays[x]->current_cell[Y]) * scene->player->vision_rays[x]->delta_ray[Y];
		}
		else
		{
			scene->player->vision_rays[x]->step[Y] = 1;
			scene->player->vision_rays[x]->side_cell[Y] = (scene->player->vision_rays[x]->current_cell[Y] + 1.0 - scene->player->vision_rays[x]->pos[Y]) * scene->player->vision_rays[x]->delta_ray[Y];
		}
		if (scene->player->vision_rays[x]->dir[X] < 0)
		{
			scene->player->vision_rays[x]->step[X] = -1;
			scene->player->vision_rays[x]->side_cell[X] = (scene->player->vision_rays[x]->pos[X] - scene->player->vision_rays[x]->current_cell[X]) * scene->player->vision_rays[x]->delta_ray[X];
		}
		else
		{
			scene->player->vision_rays[x]->step[X] = 1;
			scene->player->vision_rays[x]->side_cell[X] = (scene->player->vision_rays[x]->current_cell[X] + 1.0 - scene->player->vision_rays[x]->pos[X]) * scene->player->vision_rays[x]->delta_ray[X];
		}
		while (scene->player->vision_rays[x]->will_hit == FALSE)
		{
			if (scene->player->vision_rays[x]->side_cell[Y] < scene->player->vision_rays[x]->side_cell[X])
			{
				scene->player->vision_rays[x]->side_cell[Y] += scene->player->vision_rays[x]->delta_ray[Y];
				scene->player->vision_rays[x]->current_cell[Y] += scene->player->vision_rays[x]->step[Y];
				scene->player->vision_rays[x]->side = EW;
			}
			else
			{
				scene->player->vision_rays[x]->side_cell[X] += scene->player->vision_rays[x]->delta_ray[X];
				scene->player->vision_rays[x]->current_cell[X] += scene->player->vision_rays[x]->step[X];
				scene->player->vision_rays[x]->side = NS;
			}
			if (scene->map->map[scene->player->vision_rays[x]->current_cell[X] / UNIT][scene->player->vision_rays[x]->current_cell[Y] / UNIT] == '1')
				scene->player->vision_rays[x]->will_hit = TRUE;
		}
		if (scene->player->vision_rays[x]->side == EW)
			scene->player->vision_rays[x]->wall_dist = (scene->player->vision_rays[x]->current_cell[Y] - scene->player->vision_rays[x]->pos[Y] + (1 - scene->player->vision_rays[x]->step[Y]) / 2) / scene->player->vision_rays[x]->dir[Y];
		else
			scene->player->vision_rays[x]->wall_dist = (scene->player->vision_rays[x]->current_cell[X] - scene->player->vision_rays[x]->pos[X] + (1 - scene->player->vision_rays[x]->step[X]) / 2) / scene->player->vision_rays[x]->dir[X];
		scene->player->vision_rays[x]->wall_height = (int)(WIN_HEIGHT / scene->player->vision_rays[x]->wall_dist * 3);
		if (scene->player->vision_rays[x]->wall_height < 0)
			scene->player->vision_rays[x]->wall_height = WIN_HEIGHT;
		int	linestart = scene->player->central_angle - scene->player->is_crouching - scene->player->vision_rays[x]->wall_height / 2 + WIN_HEIGHT / 2;
		if (linestart < 0)
			linestart = 0;
		int lineend = scene->player->central_angle - scene->player->is_crouching + scene->player->vision_rays[x]->wall_height / 2 + WIN_HEIGHT / 2;
		if (lineend >= WIN_HEIGHT)
			lineend = WIN_HEIGHT - 1;
		drawline(x, linestart, x, lineend, *scene, 0x998970FF);
		// drawline_hakim(x, linestart, x, lineend, *scene, 0x998970FF);
		scene->z_buffer[x] = scene->player->vision_rays[x]->wall_dist;
		x++;
	}

}

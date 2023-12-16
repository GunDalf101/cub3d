/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_wizard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:08:25 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/15 21:47:26 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	will_hit(t_scene *scene, t_ray_caster *wizard)
{
	if (scene->map->map[scene->player->vision_rays[wizard->x]->current_cell[X]
			/ UNIT][scene->player->vision_rays[wizard->x]->current_cell[Y]
		/ UNIT] == '1')
		return (TRUE);
	return (FALSE);
}

void	dda_loop(t_scene *scene, t_ray_caster *wizard)
{
	while (scene->player->vision_rays[wizard->x]->will_hit == FALSE)
	{
		if (scene->player->vision_rays[wizard->x]->side_cell[Y] <= \
		scene->player->vision_rays[wizard->x]->side_cell[X])
		{
			scene->player->vision_rays[wizard->x]->side_cell[Y]
				+= scene->player->vision_rays[wizard->x]->delta_ray[Y];
			scene->player->vision_rays[wizard->x]->current_cell[Y]
				+= scene->player->vision_rays[wizard->x]->step[Y];
			scene->player->vision_rays[wizard->x]->side = EW;
		}
		else
		{
			scene->player->vision_rays[wizard->x]->side_cell[X]
				+= scene->player->vision_rays[wizard->x]->delta_ray[X];
			scene->player->vision_rays[wizard->x]->current_cell[X]
				+= scene->player->vision_rays[wizard->x]->step[X];
			scene->player->vision_rays[wizard->x]->side = NS;
		}
		if (will_hit(scene, wizard))
			scene->player->vision_rays[wizard->x]->will_hit = TRUE;
	}
}

void	wall_height_calculation(t_scene *scene, t_ray_caster *wizard)
{
	if (scene->player->vision_rays[wizard->x]->side == EW)
		scene->player->vision_rays[wizard->x]->wall_dist = (scene->player->\
		vision_rays[wizard->x]->side_cell[Y]
				- scene->player->vision_rays[wizard->x]->delta_ray[Y]) / UNIT;
	else
		scene->player->vision_rays[wizard->x]->wall_dist = (scene->player->\
		vision_rays[wizard->x]->side_cell[X]
				- scene->player->vision_rays[wizard->x]->delta_ray[X]) / UNIT;
	scene->player->vision_rays[wizard->x]->wall_height = (int)(WIN_HEIGHT
			/ scene->player->vision_rays[wizard->x]->wall_dist * 3 \
			* WIN_WIDTH / WIN_HEIGHT * UNIT / 100);
}

void	render_walls(t_scene *scene, t_ray_caster *wizard)
{
	if (scene->player->vision_rays[wizard->x]->wall_height < 0)
		scene->player->vision_rays[wizard->x]->wall_height = WIN_HEIGHT;
	wizard->linestart = scene->player->central_angle - scene->player->crouch
		- scene->player->vision_rays[wizard->x]->wall_height / 2 + WIN_HEIGHT
		/ 2;
	wizard->truestart = wizard->linestart;
	if (wizard->linestart < 0)
		wizard->linestart = 0;
	wizard->lineend = scene->player->central_angle - scene->player->crouch
		+ scene->player->vision_rays[wizard->x]->wall_height / 2 + WIN_HEIGHT
		/ 2;
	wizard->trueend = wizard->lineend;
	if (wizard->lineend > WIN_HEIGHT)
		wizard->lineend = WIN_HEIGHT;
	drawline_from_textures(scene, wizard);
}

void	ray_caster(t_scene *scene)
{
	t_ray_caster	wizard;

	wizard.x = 0;
	scene->player->vision_rays = malloc(sizeof(t_ray) * WIN_WIDTH);
	if (!scene->player->vision_rays && final_free(scene))
		exit(1);
	scene->z_buffer = malloc(sizeof(double) * WIN_WIDTH);
	if (!scene->z_buffer && occasional_free(scene) && final_free(scene))
		exit(1);
	while (wizard.x < WIN_WIDTH)
	{
		setup_rays(scene, &wizard);
		dda_loop(scene, &wizard);
		wall_height_calculation(scene, &wizard);
		render_walls(scene, &wizard);
		scene->z_buffer[wizard.x] = scene->player->\
		vision_rays[wizard.x]->wall_dist;
		wizard.x++;
	}
}

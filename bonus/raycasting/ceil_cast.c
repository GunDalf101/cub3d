/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil_cast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:46:26 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/16 01:20:23 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	get_ceiling_texture_color(t_scene *scene, t_floor_cast *ceilin)
{
	double	intensity;

	intensity = 1 / ((ceilin->current_dist * scene->light_multiplier) + 1);
	ceilin->color = ft_pixel(scene->ceil_img->pixels[scene->ceil_img->width
			* ceilin->ty * 4 + ceilin->tx * 4] * intensity,
			scene->ceil_img->pixels[scene->ceil_img->width * ceilin->ty * 4
			+ ceilin->tx * 4 + 1] * intensity,
			scene->ceil_img->pixels[scene->ceil_img->width * ceilin->ty * 4
			+ ceilin->tx * 4 + 2] * intensity,
			scene->ceil_img->pixels[scene->ceil_img->width * ceilin->ty * 4
			+ ceilin->tx * 4 + 3]);
}

void	render_ceiling_pixel(t_scene *scene, t_floor_cast *ceilin)
{
	ceilin->current_dist = WIN_HEIGHT / (2.0 * (ceilin->y
				- scene->player->crouch + scene->player->central_angle)
			- WIN_HEIGHT) * WIN_WIDTH / WIN_HEIGHT;
	ceilin->cell_x = (int)(ceilin->floor_x);
	ceilin->cell_y = (int)(ceilin->floor_y);
	ceilin->tx = ((int)(scene->trap_img->width * (ceilin->floor_x
					- ceilin->cell_x)) % scene->trap_img->width);
	ceilin->ty = ((int)(scene->trap_img->height * (ceilin->floor_y
					- ceilin->cell_y)) % scene->trap_img->height);
	get_ceiling_texture_color(scene, ceilin);
	mlx_put_pixel(scene->mlx_img, ceilin->x, WIN_HEIGHT - ceilin->y - 1,
		ceilin->color);
}

void	cray_vectors(t_scene *scene, t_floor_cast *ceilin)
{
	ceilin->ray_dir_x0 = scene->player->dir[X] / (UNIT / 3.0)
		- scene->player->plane[X] / (UNIT / 3.0);
	ceilin->ray_dir_y0 = scene->player->dir[Y] / (UNIT / 3.0)
		- scene->player->plane[Y] / (UNIT / 3.0);
	ceilin->ray_dir_x1 = scene->player->dir[X] / (UNIT / 3.0)
		+ scene->player->plane[X] / (UNIT / 3.0);
	ceilin->ray_dir_y1 = scene->player->dir[Y] / (UNIT / 3.0)
		+ scene->player->plane[Y] / (UNIT / 3.0);
	ceilin->p = ceilin->y - WIN_HEIGHT / 2 - scene->player->crouch
		+ scene->player->central_angle;
	ceilin->row_distance = (ceilin->ray_pos_z / ceilin->p) * WIN_WIDTH
		/ WIN_HEIGHT;
	ceilin->floor_step_x = ceilin->row_distance * (ceilin->ray_dir_x1
			- ceilin->ray_dir_x0) / WIN_WIDTH;
	ceilin->floor_step_y = ceilin->row_distance * (ceilin->ray_dir_y1
			- ceilin->ray_dir_y0) / WIN_WIDTH;
	ceilin->floor_x = ceilin->row_distance * ceilin->ray_dir_x0
		+ scene->player->pos[X] / (UNIT);
	ceilin->floor_y = ceilin->row_distance * ceilin->ray_dir_y0
		+ scene->player->pos[Y] / (UNIT);
}

void	ceiling_casting(t_scene *scene)
{
	t_floor_cast	ceilin;

	ceilin.y = WIN_HEIGHT / 2 + scene->player->crouch
		- scene->player->central_angle;
	ceilin.ray_pos_z = 0.5 * WIN_HEIGHT;
	while (ceilin.y < WIN_HEIGHT - 1)
	{
		cray_vectors(scene, &ceilin);
		ceilin.x = 0;
		while (ceilin.x < WIN_WIDTH - 1)
		{
			render_ceiling_pixel(scene, &ceilin);
			ceilin.floor_x += ceilin.floor_step_x;
			ceilin.floor_y += ceilin.floor_step_y;
			ceilin.x++;
		}
		ceilin.y++;
	}
}

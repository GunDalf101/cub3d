/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil_cast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:46:26 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/14 05:13:32 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	get_ceiling_texture_color(t_scene *scene, t_floor_cast *ceilin)
{
	double	intensity;

	intensity = 1 / ((ceilin->current_dist * 0.3) + 1);
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
	ceilin->weight = ceilin->current_dist / ceilin->row_distance;
	ceilin->current_floor_x = ceilin->weight * ceilin->floor_x + (1.0
			- ceilin->weight) * scene->player->pos[X] / 3;
	ceilin->current_floor_y = ceilin->weight * ceilin->floor_y + (1.0
			- ceilin->weight) * scene->player->pos[Y] / 3;
	ceilin->tx = (int)(scene->ceil_img->width * (ceilin->current_floor_x)
			/ (UNIT / 3.0)) % scene->ceil_img->width;
	ceilin->ty = (int)(scene->ceil_img->height * (ceilin->current_floor_y)
			/ (UNIT / 3.0)) % scene->ceil_img->height;
	get_ceiling_texture_color(scene, ceilin);
	mlx_put_pixel(scene->mlx_img, ceilin->x, WIN_HEIGHT - ceilin->y - 1,
		ceilin->color);
}

void	cray_vectors(t_scene *scene, t_floor_cast *ceilin)
{
	ceilin->ray_dir_x0 = scene->player->dir[X] - scene->player->plane[X];
	ceilin->ray_dir_y0 = scene->player->dir[Y] - scene->player->plane[Y];
	ceilin->ray_dir_x1 = scene->player->dir[X] + scene->player->plane[X];
	ceilin->ray_dir_y1 = scene->player->dir[Y] + scene->player->plane[Y];
	ceilin->p = ceilin->y - WIN_HEIGHT;
	ceilin->ray_pos_z = 0.5 * WIN_HEIGHT;
	ceilin->row_distance = ceilin->ray_pos_z / ceilin->p;
	ceilin->floor_step_x = ceilin->row_distance * (ceilin->ray_dir_x1
			- ceilin->ray_dir_x0) / WIN_WIDTH;
	ceilin->floor_step_y = ceilin->row_distance * (ceilin->ray_dir_y1
			- ceilin->ray_dir_y0) / WIN_WIDTH;
	ceilin->floor_x = ceilin->row_distance * ceilin->ray_dir_x0
		+ scene->player->pos[X] / 3;
	ceilin->floor_y = ceilin->row_distance * ceilin->ray_dir_y0
		+ scene->player->pos[Y] / 3;
}

void	ceiling_casting(t_scene *scene)
{
	t_floor_cast	ceilin;

	ceilin.y = WIN_HEIGHT / 2 + scene->player->crouch
		- scene->player->central_angle;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_cast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:46:30 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/16 01:58:30 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	is_trap(t_scene *scene, t_floor_cast *floor)
{
	if (floor->cell_y > 0 && floor->cell_x > 0
		&& floor->cell_y < scene->map->map_width
		&& floor->cell_x < scene->map->map_height
		&& scene->map->map[(int)(floor->cell_x)][(int)(floor->cell_y)] == 'T')
		return (1);
	return (0);
}

void	get_floor_texture_color(t_scene *scene, t_floor_cast *floor)
{
	double	intensity;

	intensity = 1 / ((floor->current_dist * scene->light_multiplier) + 1);
	floor->color = ft_pixel(scene->floor_img->pixels[scene->floor_img->width
			* floor->ty * 4 + floor->tx * 4] * intensity,
			scene->floor_img->pixels[scene->floor_img->width * floor->ty * 4
			+ floor->tx * 4 + 1] * intensity,
			scene->floor_img->pixels[scene->floor_img->width * floor->ty * 4
			+ floor->tx * 4 + 2] * intensity,
			scene->floor_img->pixels[scene->floor_img->width * floor->ty * 4
			+ floor->tx * 4 + 3]);
	if (is_trap(scene, floor))
		floor->color = test_color(scene, floor);
}

void	render_floor_pixel(t_scene *scene, t_floor_cast *floor)
{
	floor->current_dist = WIN_HEIGHT / (2.0 * (floor->y + scene->player->crouch
				- scene->player->central_angle) - WIN_HEIGHT) * WIN_WIDTH
		/ WIN_HEIGHT;
	floor->cell_x = (int)(floor->floor_x);
	floor->cell_y = (int)(floor->floor_y);
	floor->tx = ((int)(scene->trap_img->width * (floor->floor_x
					- floor->cell_x)) % scene->trap_img->width);
	floor->ty = ((int)(scene->trap_img->height * (floor->floor_y
					- floor->cell_y)) % scene->trap_img->height);
	get_floor_texture_color(scene, floor);
	mlx_put_pixel(scene->mlx_img, floor->x, floor->y, floor->color);
}

void	ray_vectors(t_scene *scene, t_floor_cast *floor)
{
	floor->ray_dir_x0 = scene->player->dir[X] / (UNIT / 3.0)
		- scene->player->plane[X] / (UNIT / 3.0);
	floor->ray_dir_y0 = scene->player->dir[Y] / (UNIT / 3.0)
		- scene->player->plane[Y] / (UNIT / 3.0);
	floor->ray_dir_x1 = scene->player->dir[X] / (UNIT / 3.0)
		+ scene->player->plane[X] / (UNIT / 3.0);
	floor->ray_dir_y1 = scene->player->dir[Y] / (UNIT / 3.0)
		+ scene->player->plane[Y] / (UNIT / 3.0);
	floor->p = floor->y - WIN_HEIGHT / 2 + scene->player->crouch
		- scene->player->central_angle;
	floor->row_distance = (floor->ray_pos_z / floor->p) * WIN_WIDTH
		/ WIN_HEIGHT;
	floor->floor_step_x = (floor->row_distance * (floor->ray_dir_x1
				- floor->ray_dir_x0) / WIN_WIDTH);
	floor->floor_step_y = (floor->row_distance * (floor->ray_dir_y1
				- floor->ray_dir_y0) / WIN_WIDTH);
	floor->floor_x = (floor->row_distance * floor->ray_dir_x0
			+ scene->player->pos[X] / (UNIT));
	floor->floor_y = (floor->row_distance * floor->ray_dir_y0
			+ scene->player->pos[Y] / (UNIT));
}

void	floor_casting(t_scene *scene)
{
	t_floor_cast	floor;

	floor.y = WIN_HEIGHT / 2 - scene->player->crouch
		+ scene->player->central_angle;
	floor.ray_pos_z = 0.5 * WIN_HEIGHT;
	while (floor.y < WIN_HEIGHT)
	{
		ray_vectors(scene, &floor);
		floor.x = 0;
		while (floor.x < WIN_WIDTH)
		{
			render_floor_pixel(scene, &floor);
			floor.floor_x += floor.floor_step_x;
			floor.floor_y += floor.floor_step_y;
			floor.x++;
		}
		floor.y++;
	}
}

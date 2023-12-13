/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_cast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:46:30 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/13 22:32:08 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	is_trap(t_scene *scene, t_floor_cast *floor)
{
	if (floor->current_floor_y / 34.25 + scene->player->pos[Y] / (UNIT
			* 34.25) > 0 && floor->current_floor_x / 34.25
		+ scene->player->pos[X] / (UNIT * 34.25) > 0 && floor->current_floor_y
		/ 34.25 + scene->player->pos[Y] / (UNIT
			* 34.25) < scene->map->map_width && floor->current_floor_x / 34.25
		+ scene->player->pos[X] / (UNIT * 34.25) < scene->map->map_height
		&& scene->map->map[(int)(floor->current_floor_x / 34.25
			+ scene->player->pos[X] / (UNIT
				* 34.25))][(int)(floor->current_floor_y / 34.25
			+ scene->player->pos[Y] / (UNIT * 34.25))] == 'T')
			return (1);
	return (0);
}

void	get_floor_texture_color(t_scene *scene, t_floor_cast *floor)
{
	floor->color = ft_pixel(scene->floor_img->pixels[scene->floor_img->width
			* floor->ty * 4 + floor->tx * 4],
			scene->floor_img->pixels[scene->floor_img->width * floor->ty * 4
			+ floor->tx * 4 + 1],
			scene->floor_img->pixels[scene->floor_img->width * floor->ty * 4
			+ floor->tx * 4 + 2],
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
	floor->weight = floor->current_dist / floor->row_distance;
	floor->current_floor_x = floor->weight * floor->floor_x + (1.0
			- floor->weight) * scene->player->pos[X] / 3;
	floor->current_floor_y = floor->weight * floor->floor_y + (1.0
			- floor->weight) * scene->player->pos[Y] / 3;
	floor->tx = (int)(scene->trap_img->width * (floor->current_floor_x) / 33.5)
		% scene->trap_img->width;
	floor->ty = (int)(scene->trap_img->height * (floor->current_floor_y) / 33.5)
		% scene->trap_img->height;
	get_floor_texture_color(scene, floor);
	mlx_put_pixel(scene->mlx_img, floor->x, floor->y, floor->color);
}

void	ray_vectors(t_scene *scene, t_floor_cast *floor)
{
	floor->ray_dir_x0 = scene->player->dir[X] - scene->player->plane[X];
	floor->ray_dir_y0 = scene->player->dir[Y] - scene->player->plane[Y];
	floor->ray_dir_x1 = scene->player->dir[X] + scene->player->plane[X];
	floor->ray_dir_y1 = scene->player->dir[Y] + scene->player->plane[Y];
	floor->p = floor->y - WIN_HEIGHT;
	floor->ray_pos_z = 0.5 * WIN_HEIGHT;
	floor->row_distance = floor->ray_pos_z / floor->p;
	floor->floor_step_x = floor->row_distance * (floor->ray_dir_x1
			- floor->ray_dir_x0) / WIN_WIDTH;
	floor->floor_step_y = floor->row_distance * (floor->ray_dir_y1
			- floor->ray_dir_y0) / WIN_WIDTH;
	floor->floor_x = floor->row_distance * floor->ray_dir_x0
		+ scene->player->pos[X] / 3;
	floor->floor_y = floor->row_distance * floor->ray_dir_y0
		+ scene->player->pos[Y] / 3;
}

void	floor_casting(t_scene *scene)
{
	t_floor_cast	floor;

	floor.y = WIN_HEIGHT / 2 - scene->player->crouch
		+ scene->player->central_angle;
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

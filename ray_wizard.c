/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_wizard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:08:25 by mbennani          #+#    #+#             */
/*   Updated: 2023/11/30 19:46:58 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ray_caster(t_scene *scene)
{
	int		x;
	x = 0;
	floor_casting(scene);
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
			if (scene->player->vision_rays[x]->side_cell[Y] <= scene->player->vision_rays[x]->side_cell[X])
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
		int truestart = linestart;
		if (linestart < 0)
			linestart = 0;
		int lineend = scene->player->central_angle - scene->player->is_crouching + scene->player->vision_rays[x]->wall_height / 2 + WIN_HEIGHT / 2;
		int trueend = lineend;
		if (lineend > WIN_HEIGHT)
			lineend = WIN_HEIGHT - 1;
		// drawline(x, linestart, x, lineend, *scene, 0x998970FF);
		drawline_from_textures(scene, x, linestart, lineend, truestart, trueend);
		scene->z_buffer[x] = scene->player->vision_rays[x]->wall_dist;
		
		// // FLOOR CASTING
		// double floorXWall, floorYWall;
		// if (scene->player->vision_rays[x]->side == 0 && scene->player->vision_rays[x]->dir[X] > 0)
		// {
		// 	floorXWall = scene->player->vision_rays[x]->current_cell[X];
		// 	floorYWall = scene->player->vision_rays[x]->current_cell[Y] + scene->player->vision_rays[x]->side_cell[Y];
		// }
		// else if (scene->player->vision_rays[x]->side == 0 && scene->player->vision_rays[x]->dir[X] < 0)
		// {
		// 	floorXWall = scene->player->vision_rays[x]->current_cell[X] + 1.0;
		// 	floorYWall = scene->player->vision_rays[x]->current_cell[Y] + scene->player->vision_rays[x]->side_cell[Y];
		// }
		// else if (scene->player->vision_rays[x]->side == 1 && scene->player->vision_rays[x]->dir[Y] > 0)
		// {
		// 	floorXWall = scene->player->vision_rays[x]->current_cell[X] + scene->player->vision_rays[x]->side_cell[X];
		// 	floorYWall = scene->player->vision_rays[x]->current_cell[Y];
		// }
		// else
		// {
		// 	floorXWall = scene->player->vision_rays[x]->current_cell[X] + scene->player->vision_rays[x]->side_cell[X];
		// 	floorYWall = scene->player->vision_rays[x]->current_cell[Y] + 1.0;
		// }
		
		// double distWall, distPlayer, currentDist;
		// distWall = scene->player->vision_rays[x]->wall_dist / 3;
		// distPlayer = 0.0;
		// if (lineend < 0)
		// 	lineend = WIN_HEIGHT;
		// int y = lineend + 1;
		// while(y < WIN_HEIGHT)
		// {
		// 	currentDist = WIN_HEIGHT / (2.0 * y - WIN_HEIGHT);
		// 	double weight = (currentDist - distPlayer) / (distWall - distPlayer);
		// 	double currentFloorX = weight * floorXWall + (1.0 - weight) * scene->player->pos[X];
		// 	double currentFloorY = weight * floorYWall + (1.0 - weight) * scene->player->pos[Y];
		// 	int floorTexX, floorTexY;
		// 	floorTexX = ((int)(currentFloorX * scene->map->textures_mlx_imgs[0]->width / (33.5 * 3)) % scene->map->textures_mlx_imgs[0]->width);
		// 	floorTexY = ((int)(currentFloorY * scene->map->textures_mlx_imgs[0]->height / (33.5 * 3)) % scene->map->textures_mlx_imgs[0]->height);
		// 	int color = ft_pixel(scene->map->textures_mlx_imgs[0]->pixels[scene->map->textures_mlx_imgs[0]->width * floorTexY * 4 + floorTexX * 4], scene->map->textures_mlx_imgs[0]->pixels[scene->map->textures_mlx_imgs[0]->width * floorTexY * 4 + floorTexX * 4 + 1], scene->map->textures_mlx_imgs[0]->pixels[scene->map->textures_mlx_imgs[0]->width * floorTexY * 4 + floorTexX * 4 + 2], scene->map->textures_mlx_imgs[0]->pixels[scene->map->textures_mlx_imgs[0]->width * floorTexY * 4 + floorTexX * 4 + 3]);
		// 	printf("FloorTexX: %d\n", (int)currentFloorX / UNIT);
		// 	printf("FloorTexY: %d\n", (int)currentFloorY / UNIT);
		// 	if (currentFloorY / UNIT < scene->map->map_height && currentFloorX / UNIT < scene->map->map_width && scene->map->map[(int)(currentFloorY / UNIT)][(int)(currentFloorX / UNIT)] == 'M')
        //         color = ft_pixel(scene->map->textures_mlx_imgs[2]->pixels[scene->map->textures_mlx_imgs[2]->width * floorTexY * 4 + floorTexX * 4], scene->map->textures_mlx_imgs[2]->pixels[scene->map->textures_mlx_imgs[2]->width * floorTexY * 4 + floorTexX * 4 + 1], scene->map->textures_mlx_imgs[2]->pixels[scene->map->textures_mlx_imgs[2]->width * floorTexY * 4 + floorTexX * 4 + 2], scene->map->textures_mlx_imgs[2]->pixels[scene->map->textures_mlx_imgs[2]->width * floorTexY * 4 + floorTexX * 4 + 3]);
		// 	mlx_put_pixel(scene->mlx_img, x, y, color);
		// 	y++;
		// }
		x++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 00:46:52 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/24 02:02:35 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include<unistd.h>
#include <stdio.h>
#include <stdlib.h>

int map[10][10] = {{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
					{'1', '0', '0', '0', '1', '1', '0', '0', '0', '0'},
					{'1', '0', '0', '0', '1', '1', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '1', '1', '0', '0', '0', '0'},
					{'1', '0', '0', '0', '1', '1', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '1', '1', '0', '0', '0', '1'},
					{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};


void drawline(int x1, int y1, int x2, int y2, t_scene scene, int color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {

        mlx_put_pixel(scene.mlx_img, x1, y1, color);

        if (x1 == x2 && y1 == y2) {
            break;
        }

        int err2 = 2 * err;

        if (err2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (err2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}


void	renderitall(t_scene scene)
{
	int height = WIN_HEIGHT / scene.map->map_height / 5;
	int width = WIN_WIDTH / scene.map->map_width / 5;
	int j = 0;
	// drawing map grid



	int i = 0;
	while (i < scene.map->map_height)
	{
		j = 0;
		while (j < scene.map->map_width)
		{
			if (map[i][j] == '1')
			{
				int k = 0;
				while (k < height)
				{
					int l = 0;
					while (l < width)
					{
						mlx_put_pixel(scene.mlx_img, j * width + l, i * height + k, 0xFFFFFFFF);
						l++;
					}
					k++;
				}
			}
			j++;
		}
		i++;
	}
	
	i = 1;
	while (i < scene.map->map_height)
	{
		j = 1;
		while (j < WIN_HEIGHT / 5 - 2)
		{
			mlx_put_pixel(scene.mlx_img, j, i * height , 0x808080FF);
			j++;
		}
		i++;
	}

	i = 1;
	while (i < scene.map->map_width)
	{
		j = 1;
		while (j < WIN_HEIGHT / 5 - 2)
		{
			mlx_put_pixel(scene.mlx_img, i * width, j, 0x808080FF);
			j++;
		}
		i++;
	}
	
	mlx_put_pixel(scene.mlx_img, scene.player->pos[X] / 5, scene.player->pos[Y] / 5, 0xFF0000FF);
	mlx_put_pixel(scene.mlx_img, (scene.player->pos[X] + scene.player->dir[X]) / 5, (scene.player->pos[Y] + scene.player->dir[Y]) / 5, 0xFF0000FF);
	drawline(scene.player->pos[X] / 5, scene.player->pos[Y] / 5, (scene.player->pos[X] + scene.player->dir[X]) / 5, (scene.player->pos[Y] + scene.player->dir[Y]) / 5, scene, 0x00FF00FF);
	drawline((scene.player->pos[X] + scene.player->dir[X]) / 5, (scene.player->pos[Y] + scene.player->dir[Y]) / 5, (scene.player->pos[X] + scene.player->dir[X] + scene.player->plane[X]) / 5, (scene.player->pos[Y] + scene.player->dir[Y] + scene.player->plane[Y]) / 5, scene, 0x0000FFFF);
	drawline((scene.player->pos[X] + scene.player->dir[X]) / 5, (scene.player->pos[Y] + scene.player->dir[Y]) / 5, (scene.player->pos[X] + scene.player->dir[X] - scene.player->plane[X]) / 5, (scene.player->pos[Y] + scene.player->dir[Y] - scene.player->plane[Y]) / 5, scene, 0x0000FFFF);
	mlx_image_to_window(scene.mlx_ptr, scene.mlx_img, 0, 0);
}

void	ray_caster(t_scene *scene)
{
	int		x;
	int height = WIN_HEIGHT / scene->map->map_height;
	int width = WIN_WIDTH / scene->map->map_width;
	x = 0;
	scene->player->vision_rays = malloc(sizeof(t_ray) * WIN_WIDTH);
	while (x < WIN_WIDTH)
	{
		scene->camera_x = 2 * x / (double)WIN_WIDTH - 1;
		scene->player->vision_rays[x] = malloc(sizeof(t_ray));
		scene->player->vision_rays[x]->will_hit = FALSE;
		scene->player->vision_rays[x]->pos[X] = scene->player->pos[X];
		scene->player->vision_rays[x]->pos[Y] = scene->player->pos[Y];
		scene->player->vision_rays[x]->dir[X] = scene->player->dir[X] + scene->player->plane[X] * scene->camera_x;
		scene->player->vision_rays[x]->dir[Y] = scene->player->dir[Y] + scene->player->plane[Y] * scene->camera_x;
		scene->player->vision_rays[x]->current_cell[X] = (int)scene->player->vision_rays[x]->pos[X];
		scene->player->vision_rays[x]->current_cell[Y] = (int)scene->player->vision_rays[x]->pos[Y];
		if (scene->player->vision_rays[x]->dir[X] != 0)
			scene->player->vision_rays[x]->delta_ray[X] = fabs(1 / scene->player->vision_rays[x]->dir[X]);
		else
			scene->player->vision_rays[x]->delta_ray[X] = __DBL_MAX__;
		if (scene->player->vision_rays[x]->dir[Y] != 0)
			scene->player->vision_rays[x]->delta_ray[Y] = fabs(1 / scene->player->vision_rays[x]->dir[Y]);
		else
			scene->player->vision_rays[x]->delta_ray[Y] = __DBL_MAX__;
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
		while (scene->player->vision_rays[x]->will_hit == FALSE)
		{
			if (scene->player->vision_rays[x]->side_cell[X] < scene->player->vision_rays[x]->side_cell[Y])
			{
				scene->player->vision_rays[x]->side_cell[X] += scene->player->vision_rays[x]->delta_ray[X];
				scene->player->vision_rays[x]->current_cell[X] += scene->player->vision_rays[x]->step[X];
				scene->player->vision_rays[x]->side = EW;
			}
			else
			{
				scene->player->vision_rays[x]->side_cell[Y] += scene->player->vision_rays[x]->delta_ray[Y];
				scene->player->vision_rays[x]->current_cell[Y] += scene->player->vision_rays[x]->step[Y];
				scene->player->vision_rays[x]->side = NS;
			}
			if (map[scene->player->vision_rays[x]->current_cell[Y] / width][scene->player->vision_rays[x]->current_cell[X] / height] == '1')
				scene->player->vision_rays[x]->will_hit = TRUE;
		}
		if (scene->player->vision_rays[x]->side == EW)
			scene->player->vision_rays[x]->wall_dist = (scene->player->vision_rays[x]->current_cell[X] - scene->player->vision_rays[x]->pos[X] + (1 - scene->player->vision_rays[x]->step[X]) / 2) / scene->player->vision_rays[x]->dir[X];
		else
			scene->player->vision_rays[x]->wall_dist = (scene->player->vision_rays[x]->current_cell[Y] - scene->player->vision_rays[x]->pos[Y] + (1 - scene->player->vision_rays[x]->step[Y]) / 2) / scene->player->vision_rays[x]->dir[Y];
		drawline(scene->player->pos[X] / 5, scene->player->pos[Y] / 5, scene->player->vision_rays[x]->current_cell[X] / 5, scene->player->vision_rays[x]->current_cell[Y] / 5, *scene, 0x00FF00FF);
		scene->player->vision_rays[x]->wall_height = (int)(WIN_HEIGHT / scene->player->vision_rays[x]->wall_dist * 2);
		if (scene->player->vision_rays[x]->wall_height < 0)
			scene->player->vision_rays[x]->wall_height = WIN_HEIGHT;
		int	linestart = - scene->player->vision_rays[x]->wall_height / 2 + WIN_HEIGHT / 2;
		if (linestart < 0)
			linestart = 0;
		int lineend = scene->player->vision_rays[x]->wall_height / 2 + WIN_HEIGHT / 2;
		if (lineend >= WIN_HEIGHT)
			lineend = WIN_HEIGHT - 1;
		drawline(x, linestart, x, lineend, *scene, 0x0000FFFF);
		// drawline(scene->player->vision_rays[x]->current_cell[X] / 5, scene->player->vision_rays[x]->current_cell[Y] / 5, scene->player->vision_rays[x]->current_cell[X] / 5 + 1, scene->player->vision_rays[x]->current_cell[Y] / 5 + 1, *scene, 0xFF0000FF);
		x++;
	}
	
}

void	hooker(struct mlx_key_data keycode, void *scene2)
{
	t_scene	*scene;
	scene = (t_scene *)scene2;
	int height = WIN_HEIGHT / scene->map->map_height;
	int width = WIN_WIDTH / scene->map->map_width;
	mlx_delete_image(scene->mlx_ptr, scene->mlx_img);
	scene->mlx_img = mlx_new_image(scene->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (keycode.key == MLX_KEY_ESCAPE)
		exit(0);
	if (keycode.key == MLX_KEY_W)
	{
		if (map[(int)(scene->player->pos[Y]) / width][(int)(scene->player->pos[X] + scene->player->dir[X] / 3) / (WIN_WIDTH / scene->map->map_width)] != '1')
			scene->player->pos[X] += scene->player->dir[X] / 3;
		if (map[(int)(scene->player->pos[Y] + scene->player->dir[Y] / 3) / (WIN_HEIGHT / scene->map->map_height)][(int)(scene->player->pos[X]) / height] != '1')
			scene->player->pos[Y] += scene->player->dir[Y] / 3;
		
	}
	if (keycode.key == MLX_KEY_S)
	{
		if (map[(int)(scene->player->pos[Y]) / width][(int)(scene->player->pos[X] - scene->player->dir[X] / 3) / (WIN_WIDTH / scene->map->map_width)] != '1')
			scene->player->pos[X] -= scene->player->dir[X] / 3;
		if (map[(int)(scene->player->pos[Y] - scene->player->dir[Y] / 3) / (WIN_HEIGHT / scene->map->map_height)][(int)(scene->player->pos[X]) / height] != '1')
			scene->player->pos[Y] -= scene->player->dir[Y] / 3;
	}
	if (keycode.key == MLX_KEY_A)
	{
		scene->player->p_angle -= 0.1;
		if (scene->player->p_angle > 2 * M_PI)
			scene->player->p_angle -= 2 * M_PI;
		scene->player->dir[X] = (double)cosf(scene->player->p_angle) * 25;
		scene->player->dir[Y] = (double)sinf(scene->player->p_angle) * 25;
		scene->player->plane[X] = (double)cosf(scene->player->p_angle + M_PI / 2) * 16.5;
		scene->player->plane[Y] = (double)sinf(scene->player->p_angle + M_PI / 2) * 16.5;
	}
	if (keycode.key == MLX_KEY_D)
	{
		scene->player->p_angle += 0.1;
		if (scene->player->p_angle < 0)
			scene->player->p_angle += 2 * M_PI;
		scene->player->dir[X] = (double)cosf(scene->player->p_angle) * 25;
		scene->player->dir[Y] = (double)sinf(scene->player->p_angle) * 25;
		scene->player->plane[X] = (double)cosf(scene->player->p_angle + M_PI / 2) * 16.5;
		scene->player->plane[Y] = (double)sinf(scene->player->p_angle + M_PI / 2) * 16.5;
	}
	ray_caster(scene);
	renderitall(*scene);
}

int	main()
{
	t_scene		scene;
	scene.player = malloc(sizeof(t_player));
	scene.player->pos[X] = 150;
	scene.player->pos[Y] = 150;
	scene.player->p_angle = 0;
	scene.player->dir[X] = (double)cosf(scene.player->p_angle) * 25;
	scene.player->dir[Y] = (double)sinf(scene.player->p_angle) * 25;
	scene.player->plane[X] = (double)cosf(scene.player->p_angle + M_PI / 2) * 16.5;
	scene.player->plane[Y] = (double)sinf(scene.player->p_angle + M_PI / 2) * 16.5;
	scene.map = malloc(sizeof(t_map));
	scene.map->map_height = 10;
	scene.map->map_width = 10;
	scene.mlx_ptr = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Escape From GunDalf", 1);
	scene.mlx_img = mlx_new_image(scene.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx_key_hook(scene.mlx_ptr, hooker, &scene);
	ray_caster(&scene);
	renderitall(scene);
	mlx_loop(scene.mlx_ptr);
	return (0);
}
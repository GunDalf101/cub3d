/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 00:46:52 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/24 14:16:59 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include<unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	ray_caster(t_scene *scene);

int map[11][10] = {{'0', '1', '1', '1', '1', '1', '1', '1', '1', '0'},
					{'1', 'N', 'T', 'T', '1', '1', '0', '0', '0', '1'},
					{'1', 'T', '0', '0', '1', '1', '0', '0', '0', '1'},
					{'1', 'T', '0', '0', '0', '1', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
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

void	drawbar(t_scene scene)
{
	int i = 0;
	int healthbar = scene.player->health_points * 2;
	int manabar = scene.player->mana_points * 2;
	while (i < 20 && healthbar > 0)
	{
		drawline(50 , i + WIN_HEIGHT - 60, 50 + healthbar, i + WIN_HEIGHT - 60, scene, 0xFF0000FF);
		i++;
	}
	i = 0;
	while (i < 20 && manabar > 0)
	{
		drawline(50 , i + WIN_HEIGHT - 35, 50 + manabar, i + WIN_HEIGHT - 35, scene, 0x0000FFFF);
		i++;
	}
}

void	renderitall(t_scene scene)
{
	int height = WIN_HEIGHT / scene.map->map_width / 5;
	int width = WIN_WIDTH / scene.map->map_height / 5;
	int j = 0;
	// drawing map grid


	int i = 0;
	while (i < WIN_HEIGHT / 2)
	{
		drawline(0 , i, WIN_WIDTH, i, scene, 0x87CEEBFF);
		i++;
	}
	i = WIN_HEIGHT / 2;
	while (i < WIN_HEIGHT)
	{
		drawline(0 , i, WIN_WIDTH, i, scene, 0x9b7653FF);
		i++;
	}
	ray_caster(&scene);
	i = 0;
	while (i < scene.map->map_width)
	{
		j = 0;
		while (j < scene.map->map_height)
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
	while (i < scene.map->map_width + 1)
	{
		j = 1;
		while (j < WIN_WIDTH / 5)
		{
			mlx_put_pixel(scene.mlx_img, j, i * height , 0x808080FF);
			j++;
		}
		i++;
	}

	i = 1;
	while (i < scene.map->map_height + 1)
	{
		j = 1;
		while (j < WIN_HEIGHT / 5)
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
	drawbar(scene);
	mlx_image_to_window(scene.mlx_ptr, scene.mlx_img, 0, 0);
	if (scene.player->is_ded == TRUE)
	{
		mlx_put_string(scene.mlx_ptr, "YOU DIED", WIN_WIDTH / 2 - 50, WIN_HEIGHT / 2);
		mlx_put_string(scene.mlx_ptr, "GAME OVER", WIN_WIDTH / 2 - 50, WIN_HEIGHT / 2 + 20);
	}
}

void	ray_caster(t_scene *scene)
{
	int		x;
	int height = WIN_HEIGHT / scene->map->map_width;
	int width = WIN_WIDTH / scene->map->map_height;
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
		scene->player->vision_rays[x]->wall_height = (int)(WIN_HEIGHT / scene->player->vision_rays[x]->wall_dist * 3);
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

void	game_logic(t_scene *scene)
{
	int height = WIN_HEIGHT / scene->map->map_width;
	int width = WIN_WIDTH / scene->map->map_height;
	if (scene->player->health_points <= 0)
		scene->player->is_ded = TRUE;
	if (map[(int)(scene->player->pos[Y]) / width][(int)(scene->player->pos[X]) / height] == 'T' && scene->player->health_points > 0 && (scene->key_data.key == MLX_KEY_W || scene->key_data.key == MLX_KEY_S) && (scene->key_data.action == 1 || scene->key_data.action == 2))
	{
		scene->player->health_points -= 10;
		map[(int)(scene->player->pos[Y]) / width][(int)(scene->player->pos[X]) / height] = 'T';
	}
}

void	hooker(mlx_key_data_t keycode, void *scene2)
{
	t_scene	*scene;
	scene = (t_scene *)scene2;
	int height = WIN_HEIGHT / scene->map->map_width;
	int width = WIN_WIDTH / scene->map->map_height;
	scene->key_data = keycode;
	mlx_delete_image(scene->mlx_ptr, scene->mlx_img);
	scene->mlx_img = mlx_new_image(scene->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (keycode.key == MLX_KEY_ESCAPE)
		exit(0);
	if (keycode.key == MLX_KEY_W)
	{
		if (map[(int)(scene->player->pos[Y]) / width][(int)(scene->player->pos[X] + scene->player->dir[X] / 3) / (WIN_WIDTH / scene->map->map_height)] != '1')
			scene->player->pos[X] += scene->player->dir[X] / 3;
		if (map[(int)(scene->player->pos[Y] + scene->player->dir[Y] / 3) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[X]) / height] != '1')
			scene->player->pos[Y] += scene->player->dir[Y] / 3;
		
	}
	if (keycode.key == MLX_KEY_S)
	{
		if (map[(int)(scene->player->pos[Y]) / width][(int)(scene->player->pos[X] - scene->player->dir[X] / 3) / (WIN_WIDTH / scene->map->map_height)] != '1')
			scene->player->pos[X] -= scene->player->dir[X] / 3;
		if (map[(int)(scene->player->pos[Y] - scene->player->dir[Y] / 3) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[X]) / height] != '1')
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
	if (keycode.key == MLX_KEY_E && scene->player->mana_points >= 20 && scene->player->health_points > 0 && scene->player->health_points < 100 && keycode.action == 1)
	{
		scene->player->mana_points -= 20;
		if (scene->player->health_points + 20 > 100)
			scene->player->health_points = 100;
		else
			scene->player->health_points += 20;
	}
	printf("Health: %d\n", scene->player->health_points);
	game_logic(scene);
	renderitall(*scene);
}

void	hookercur(double xpos, double ypos, void* scene2)
{
	t_scene	*scene;
	static int i = 0;
	scene = (t_scene *)scene2;
	// int x = xpos - WIN_WIDTH / 2;
	(void)ypos;
	// int y = ypos - WIN_HEIGHT / 2;
	scene->player->p_angle = xpos / 5000;
	if (scene->player->p_angle < 0)
		scene->player->p_angle += 2 * M_PI;
	if (scene->player->p_angle > 2 * M_PI)
			scene->player->p_angle -= 2 * M_PI;
	scene->player->dir[X] = (double)cosf(scene->player->p_angle) * 25;
	scene->player->dir[Y] = (double)sinf(scene->player->p_angle) * 25;
	scene->player->plane[X] = (double)cosf(scene->player->p_angle + M_PI / 2) * 16.5;
	scene->player->plane[Y] = (double)sinf(scene->player->p_angle + M_PI / 2) * 16.5;
	printf("mouse is going wild %d\n", i);
	i++;
	game_logic(scene);
	renderitall(*scene);
}

void	initplayer(t_scene *scene)
{
	int i = 0;
	int j = 0;

	scene->player = malloc(sizeof(t_player));
	while (i < scene->map->map_width)
	{
		j = 0;
		while (j < scene->map->map_height)
		{
			if (map[i][j] == 'N')
			{
				scene->player->pos[X] = j * WIN_WIDTH / scene->map->map_height + WIN_WIDTH / scene->map->map_height / 2;
				scene->player->pos[Y] = i * WIN_HEIGHT / scene->map->map_width + WIN_HEIGHT / scene->map->map_width / 2;
			}
			j++;
		}
		i++;
	}
	scene->player->p_angle = 0;
	scene->player->dir[X] = (double)cosf(scene->player->p_angle) * 25;
	scene->player->dir[Y] = (double)sinf(scene->player->p_angle) * 25;
	scene->player->plane[X] = (double)cosf(scene->player->p_angle + M_PI / 2) * 16.5;
	scene->player->plane[Y] = (double)sinf(scene->player->p_angle + M_PI / 2) * 16.5;
	scene->player->health_points = 100;
	scene->player->mana_points = 100;
	scene->player->is_ded = FALSE;
}


int	main()
{
	t_scene		scene;
	scene.map = malloc(sizeof(t_map));
	scene.map->map_width = 11;
	scene.map->map_height = 10;
	initplayer(&scene);
	scene.mlx_ptr = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Escape From GunDalf", 1);
	scene.mlx_img = mlx_new_image(scene.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx_key_hook(scene.mlx_ptr, hooker, &scene);
	mlx_cursor_hook(scene.mlx_ptr, hookercur, &scene);
	renderitall(scene);
	mlx_loop(scene.mlx_ptr);
	return (0);
}
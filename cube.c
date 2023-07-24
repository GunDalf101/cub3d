/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 00:46:52 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/24 23:39:04 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include<unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	ray_caster(t_scene *scene);

int map[11][10] = {{'0', '1', '1', '1', '1', '1', '1', '1', '1', '0'},
					{'1', 'N', 'T', 'T', '1', '1', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '1', '1', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
					{'1', '0', '1', '1', '1', '1', '1', '1', '0', '1'},
					{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
					{'1', '0', '1', '1', '1', '1', '1', '1', '0', '1'},
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

int32_t ft_pixel(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	renderitall(t_scene scene)
{
	int height = WIN_HEIGHT / scene.map->map_width / 5;
	int width = WIN_WIDTH / scene.map->map_height / 5;
	int j = 0;
	// drawing map grid


	int i = 0;
	while (i < scene.player->central_angle + WIN_HEIGHT / 2)
	{
		drawline(0 , i, WIN_HEIGHT, i, scene, 0x87CEEBFF);
		i++;
	}
	i = scene.player->central_angle + WIN_HEIGHT / 2;
	while (i < WIN_HEIGHT)
	{
		drawline(0 , i, WIN_HEIGHT, i, scene, 0x9b7653FF);
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
	
	i = 0;
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

	i = 0;
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
	mlx_texture_t *death_screen;
	mlx_image_t		*death_img;
	death_screen = mlx_load_png("./DEAD.png");
	if (scene.player->is_ded == TRUE)
	{
		death_img = mlx_texture_to_image(scene.mlx_ptr, death_screen);
		for (u_int32_t i = 0; i < death_img->height; i++)
			for (uint32_t j = 0; j < death_img->width; j++)
			{
				u_int8_t r = death_img->pixels[i * 4 * death_img->width + j * 4];
				u_int8_t g = death_img->pixels[i * 4 * death_img->width + j * 4 + 1];
				u_int8_t b = death_img->pixels[i * 4 * death_img->width + j * 4 + 2];
				u_int8_t a = death_img->pixels[i * 4 * death_img->width + j * 4 + 3];
				if (a == 0)
					continue;
				mlx_put_pixel(scene.mlx_img, j + WIN_WIDTH / 2 - death_img->width / 2, i + WIN_HEIGHT / 2 - death_img->height / 2, ft_pixel(r, g, b, a));
			}
	}
	mlx_image_to_window(scene.mlx_ptr, scene.mlx_img, 0, 0);
	mlx_delete_texture(death_screen);
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
		int	linestart = scene->player->central_angle - scene->player->vision_rays[x]->wall_height / 2 + WIN_HEIGHT / 2;
		if (linestart < 0)
			linestart = 0;
		int lineend = scene->player->central_angle + scene->player->vision_rays[x]->wall_height / 2 + WIN_HEIGHT / 2;
		if (lineend >= WIN_HEIGHT)
			lineend = WIN_HEIGHT - 1;
		drawline(x, linestart, x, lineend, *scene, 0x998970FF);
		// drawline(scene->player->vision_rays[x]->current_cell[X] / 5, scene->player->vision_rays[x]->current_cell[Y] / 5, scene->player->vision_rays[x]->current_cell[X] / 5, scene->player->vision_rays[x]->current_cell[Y] / 5, *scene, 0xFF0000FF);
		x++;
	}
	
}

void	game_logic(t_scene *scene)
{
	int height = WIN_HEIGHT / scene->map->map_width;
	int width = WIN_WIDTH / scene->map->map_height;
	if (scene->player->health_points <= 0)
		scene->player->is_ded = TRUE;
	if (map[(int)(scene->player->pos[Y]) / width][(int)(scene->player->pos[X]) / height] == 'T' && scene->player->health_points > 0 && (scene->key_data.key == MLX_KEY_W || scene->key_data.key == MLX_KEY_S || scene->key_data.key == MLX_KEY_A || scene->key_data.key == MLX_KEY_D) && (scene->key_data.action == 1 || scene->key_data.action == 2))
	{
		if (scene->player->health_points - 15 < 0)
			scene->player->health_points = 0;
		else
			scene->player->health_points -= 15;
		map[(int)(scene->player->pos[Y]) / width][(int)(scene->player->pos[X]) / height] = '0';
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
		double delta_x = scene->player->dir[X] / 1.5;
		double delta_y = scene->player->dir[Y] / 1.5;
		if (map[(int)(scene->player->pos[Y]) / width][(int)(scene->player->pos[X] + delta_x) / (WIN_WIDTH / scene->map->map_height)] != '1')
			scene->player->pos[X] += delta_x;
		if (map[(int)(scene->player->pos[Y] + delta_y) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[X]) / height] != '1')
			scene->player->pos[Y] += delta_y;
	}
	if (keycode.key == MLX_KEY_S)
	{
		if (map[(int)(scene->player->pos[Y]) / width][(int)(scene->player->pos[X] - scene->player->dir[X] / 1.5) / (WIN_WIDTH / scene->map->map_height)] != '1')
			scene->player->pos[X] -= scene->player->dir[X] / 1.5;
		if (map[(int)(scene->player->pos[Y] - scene->player->dir[Y] / 1.5) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[X]) / height] != '1')
			scene->player->pos[Y] -= scene->player->dir[Y] / 1.5;
	}
	if (keycode.key == MLX_KEY_A)
	{
		if (map[(int)(scene->player->pos[Y]) / width][(int)(scene->player->pos[X] - scene->player->plane[X] / 1.5) / (WIN_WIDTH / scene->map->map_height)] != '1')
			scene->player->pos[X] -= scene->player->plane[X] / 1.5;
		if (map[(int)(scene->player->pos[Y] - scene->player->plane[Y] / 1.5) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[X]) / height] != '1')
			scene->player->pos[Y] -= scene->player->plane[Y] / 1.5;
	}
	if (keycode.key == MLX_KEY_D)
	{
		if (map[(int)(scene->player->pos[Y]) / width][(int)(scene->player->pos[X] + scene->player->plane[X] / 1.5) / (WIN_WIDTH / scene->map->map_height)] != '1')
			scene->player->pos[X] += scene->player->plane[X] / 1.5;
		if (map[(int)(scene->player->pos[Y] + scene->player->plane[Y] / 1.5) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[X]) / height] != '1')
			scene->player->pos[Y] += scene->player->plane[Y] / 1.5;
	}
	if (keycode.key == MLX_KEY_LEFT)
	{
		scene->player->p_angle -= 0.1;
		if (scene->player->p_angle > 2 * M_PI)
			scene->player->p_angle -= 2 * M_PI;
		scene->player->dir[X] = (double)cosf(scene->player->p_angle) * 25;
		scene->player->dir[Y] = (double)sinf(scene->player->p_angle) * 25;
		scene->player->plane[X] = (double)cosf(scene->player->p_angle + M_PI / 2) * 16.5;
		scene->player->plane[Y] = (double)sinf(scene->player->p_angle + M_PI / 2) * 16.5;
	}
	if (keycode.key == MLX_KEY_RIGHT)
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
	game_logic(scene);
}

void	hookercur(double xpos, double ypos, void* scene2)
{
	t_scene	*scene;
	static double	old_ypos;

	scene = (t_scene *)scene2;
	if (old_ypos == 0)
		old_ypos = ypos;
	scene->player->p_angle = xpos / 80;
	if (old_ypos < ypos)
		scene->player->central_angle -= 30.0;
	else if (old_ypos > ypos)
		scene->player->central_angle += 30.0;
	if (scene->player->p_angle < 0)
		scene->player->p_angle += 2 * M_PI;
	if (scene->player->p_angle > 2 * M_PI)
			scene->player->p_angle -= 2 * M_PI;
	// if (scene->player->central_angle < 0)
	// 	scene->player->central_angle += 2 * M_PI;
	// if (scene->player->central_angle > 2 * M_PI)
	// 		scene->player->central_angle -= 2 * M_PI;
	if (scene->player->central_angle > WIN_HEIGHT / 2)
		scene->player->central_angle = WIN_HEIGHT / 2;
	if (scene->player->central_angle < -WIN_HEIGHT / 3)
		scene->player->central_angle = -WIN_HEIGHT / 3;
	printf("central angle : %f\n", scene->player->central_angle);
	scene->player->dir[X] = (double)cosf(scene->player->p_angle) * 25;
	scene->player->dir[Y] = (double)sinf(scene->player->p_angle) * 25;
	scene->player->plane[X] = (double)cosf(scene->player->p_angle + M_PI / 2) * 16.5;
	scene->player->plane[Y] = (double)sinf(scene->player->p_angle + M_PI / 2) * 16.5;
	old_ypos = ypos;
	game_logic(scene);
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
	scene->player->central_angle = 0;
	scene->player->is_ded = FALSE;
}

void	gameloop(void *scene2)
{
	t_scene	*scene;
	scene = (t_scene *)scene2;
	renderitall(*scene);
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
	mlx_loop_hook(scene.mlx_ptr, gameloop, &scene);
	mlx_set_cursor_mode(scene.mlx_ptr, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(scene.mlx_ptr, hookercur, &scene);
	mlx_key_hook(scene.mlx_ptr, hooker, &scene);
	renderitall(scene);
	mlx_loop(scene.mlx_ptr);
	return (0);
}
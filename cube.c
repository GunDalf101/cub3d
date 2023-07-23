/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 00:46:52 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/23 14:35:12 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include<unistd.h>
#include <stdio.h>
#include <stdlib.h>

int map[10][10] = {{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
					{'1', '0', '0', '0', '1', '1', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '1', '1', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '1', '1', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '1', '1', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '1', '1', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '1', '1', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '1', '1', '0', '0', '0', '1'},
					{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};


void drawline(int x1, int y1, int x2, int y2, t_scene scene) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {

        mlx_put_pixel(scene.mlx_img, x1, y1, 0x00FF00FF);

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
	printf("rendering\n");
	int height = WIN_HEIGHT / scene.map->map_height;
	int width = WIN_WIDTH / scene.map->map_width;
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
		while (j < WIN_HEIGHT)
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
		while (j < WIN_HEIGHT)
		{
			mlx_put_pixel(scene.mlx_img, i * width, j, 0x808080FF);
			j++;
		}
		i++;
	}
	
	mlx_put_pixel(scene.mlx_img, scene.player->pos[X], scene.player->pos[Y], 0xFF0000FF);
	mlx_put_pixel(scene.mlx_img, scene.player->pos[X] + scene.player->dir[X], scene.player->pos[Y] + scene.player->dir[Y], 0x00FF00FF);
	drawline(scene.player->pos[X], scene.player->pos[Y], scene.player->pos[X] + scene.player->dir[X], scene.player->pos[Y] + scene.player->dir[Y], scene);
	mlx_image_to_window(scene.mlx_ptr, scene.mlx_img, 0, 0);
}

void	hooker(struct mlx_key_data keycode, void *scene2)
{
	t_scene	*scene;
	scene = (t_scene *)scene2;
	mlx_delete_image(scene->mlx_ptr, scene->mlx_img);
	scene->mlx_img = mlx_new_image(scene->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	printf("keycode: %d\n", keycode.key);
	if (keycode.key == MLX_KEY_ESCAPE)
		exit(0);
	if (keycode.key == MLX_KEY_W)
	{
		scene->player->pos[X] += scene->player->dir[X];
		scene->player->pos[Y] += scene->player->dir[Y];
		
	}
	if (keycode.key == MLX_KEY_S)
	{
		scene->player->pos[X] -= scene->player->dir[X];
		scene->player->pos[Y] -= scene->player->dir[Y];
	}
	if (keycode.key == MLX_KEY_A)
	{
		scene->player->p_angle -= 0.1;
		if (scene->player->p_angle > 2 * 3.14)
			scene->player->p_angle -= 2 * 3.14;
		scene->player->dir[X] = (double)cosf(scene->player->p_angle) * 25;
		scene->player->dir[Y] = (double)sinf(scene->player->p_angle) * 25;
	}
	if (keycode.key == MLX_KEY_D)
	{
		scene->player->p_angle += 0.1;
		if (scene->player->p_angle < 0)
			scene->player->p_angle += 2 * 3.14;
		scene->player->dir[X] = (double)cosf(scene->player->p_angle) * 25;
		scene->player->dir[Y] = (double)sinf(scene->player->p_angle) * 25;
	}
	renderitall(*scene);
}

int	main()
{
	t_scene		scene;
	printf("map: %d\n", 1010);
	scene.player = malloc(sizeof(t_player));
	scene.player->pos[X] = 105;
	scene.player->pos[Y] = 105;
	scene.player->p_angle = 0;
	scene.player->dir[X] = (double)cosf(scene.player->p_angle) * 25;
	scene.player->dir[Y] = (double)sinf(scene.player->p_angle) * 25;
	scene.map = malloc(sizeof(t_map));
	scene.map->map_height = 10;
	scene.map->map_width = 10;
	scene.mlx_ptr = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Escape From GunDalf", 1);
	scene.mlx_img = mlx_new_image(scene.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx_key_hook(scene.mlx_ptr, hooker, &scene);
	renderitall(scene);
	mlx_loop(scene.mlx_ptr);
	return (0);
}
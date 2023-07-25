/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:16:36 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/25 21:23:03 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

extern int map[11][10];

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

int32_t	ft_pixel(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a)
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
	if (scene.player->is_ded == TRUE)
	{
		i = 2 * WIN_HEIGHT / 5;
		while (i < WIN_HEIGHT - 2 * WIN_HEIGHT / 5)
		{
			j = 0;
			while (j < WIN_WIDTH)
			{
				if (i % 3 != 0 || j % 3 != 0)
					mlx_put_pixel(scene.mlx_img, j, i, 0x00000000);
				j++;
			}
			i++;
		}
		mlx_texture_t *death_screen;
		mlx_image_t		*death_img;
		death_screen = mlx_load_png("./DEAD.png");
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
		mlx_delete_image(scene.mlx_ptr, death_img);
		mlx_delete_texture(death_screen);
	}
	mlx_image_to_window(scene.mlx_ptr, scene.mlx_img, 0, 0);
}

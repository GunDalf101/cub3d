/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GunDalf <GunDalf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:16:36 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/26 17:24:21 by GunDalf          ###   ########.fr       */
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

void	spawn_sprites(t_scene *scene, int count)
{
	scene->sprites[count]->relative_pos[Y] = scene->sprites[count]->pos[Y] - scene->player->pos[Y];
	scene->sprites[count]->relative_pos[X] = scene->sprites[count]->pos[X] - scene->player->pos[X];
	scene->sprites[count]->inverse_det = 1.0 / (scene->player->plane[Y] * scene->player->dir[X] - scene->player->dir[Y] * scene->player->plane[X]);
	scene->sprites[count]->transform[Y] = scene->sprites[count]->inverse_det * (-scene->player->plane[X] * scene->sprites[count]->relative_pos[Y] + scene->player->plane[Y] * scene->sprites[count]->relative_pos[X]);
	scene->sprites[count]->transform[X] = scene->sprites[count]->inverse_det * (scene->player->dir[X] * scene->sprites[count]->relative_pos[Y] - scene->player->dir[Y] * scene->sprites[count]->relative_pos[X]);
	scene->sprites[count]->v_move_screen = (int)(scene->sprites[count]->v_move / scene->sprites[count]->transform[Y]);
	scene->sprites[count]->sprite_screen_x = (int)((WIN_WIDTH / 2) * (1 + scene->sprites[count]->transform[X] / scene->sprites[count]->transform[Y]));
	scene->sprites[count]->sprite_height = abs((int)(scene->sprites[count]->sprite_img->height / (scene->sprites[count]->transform[Y]) * 7));
	scene->sprites[count]->start[Y] = - scene->sprites[count]->sprite_height / 2 + WIN_HEIGHT / 2 + scene->sprites[count]->v_move_screen;
	if (scene->sprites[count]->start[Y] < - scene->player->central_angle + scene->player->is_crouching)
		scene->sprites[count]->start[Y] = - scene->player->central_angle + scene->player->is_crouching;
	scene->sprites[count]->end[Y] =  scene->sprites[count]->sprite_height / 2 + WIN_HEIGHT / 2 + scene->sprites[count]->v_move_screen;
	if (scene->sprites[count]->end[Y] >= WIN_HEIGHT - scene->player->central_angle + scene->player->is_crouching)
		scene->sprites[count]->end[Y] = WIN_HEIGHT - scene->player->central_angle + scene->player->is_crouching - 1;
	scene->sprites[count]->sprite_width = abs((int)(scene->sprites[count]->sprite_img->width / (scene->sprites[count]->transform[Y]) * 7));
	scene->sprites[count]->start[X] = scene->sprites[count]->sprite_screen_x - scene->sprites[count]->sprite_width / 2;
	if (scene->sprites[count]->start[X] < 0)
		scene->sprites[count]->start[X] = 0;
	scene->sprites[count]->end[X] = scene->sprites[count]->sprite_screen_x + scene->sprites[count]->sprite_width / 2;
	if (scene->sprites[count]->end[X] >= WIN_WIDTH)
		scene->sprites[count]->end[X] = WIN_WIDTH - 1;
	for (int stripe = scene->sprites[count]->start[X]; stripe < scene->sprites[count]->end[X]; stripe++)
	{
		scene->sprites[count]->tex[X] = (int)(256 * (stripe - (-scene->sprites[count]->sprite_width / 2 + scene->sprites[count]->sprite_screen_x)) * scene->sprites[count]->sprite_img->width / scene->sprites[count]->sprite_width) / 256;
		if (stripe > 0 && stripe < WIN_WIDTH && scene->sprites[count]->transform[Y] > 0 && scene->sprites[count]->transform[Y] < scene->z_buffer[stripe])
		for (int j = scene->sprites[count]->start[Y]; j < scene->sprites[count]->end[Y]; j++)
		{
			scene->sprites[count]->d  = (j - scene->sprites[count]->v_move_screen) * 256 - WIN_HEIGHT * 128 + scene->sprites[count]->sprite_height * 128;
			scene->sprites[count]->tex[Y] = ((scene->sprites[count]->d * scene->sprites[count]->sprite_img->height) / scene->sprites[count]->sprite_height) / 256;
			u_int8_t r = scene->sprites[count]->sprite_img->pixels[scene->sprites[count]->tex[Y] * 4 * scene->sprites[count]->sprite_img->width + scene->sprites[count]->tex[X] * 4];
			u_int8_t g = scene->sprites[count]->sprite_img->pixels[scene->sprites[count]->tex[Y] * 4 * scene->sprites[count]->sprite_img->width + scene->sprites[count]->tex[X] * 4 + 1];
			u_int8_t b = scene->sprites[count]->sprite_img->pixels[scene->sprites[count]->tex[Y] * 4 * scene->sprites[count]->sprite_img->width + scene->sprites[count]->tex[X] * 4 + 2];
			u_int8_t a = scene->sprites[count]->sprite_img->pixels[scene->sprites[count]->tex[Y] * 4 * scene->sprites[count]->sprite_img->width + scene->sprites[count]->tex[X] * 4 + 3];
			if (a == 0)
				continue;
			mlx_put_pixel(scene->mlx_img, stripe, scene->player->central_angle - scene->player->is_crouching + j, ft_pixel(r, g, b, a));
		}
	}
}

//sort sprites by distance

void	sort_sprites(t_sprite **sprites, int count)
{
	int i = 0;
	int j = 0;
	t_sprite *tmp;
	while (i < count)
	{
		j = 0;
		while (j < count - 1)
		{
			if (sprites[j]->sprite_distance < sprites[j + 1]->sprite_distance)
			{
				tmp = sprites[j];
				sprites[j] = sprites[j + 1];
				sprites[j + 1] = tmp;
			}
			j++;
		}
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
	while (i < scene.player->central_angle + WIN_HEIGHT / 2 - scene.player->is_crouching)
	{
		drawline(0 , i, WIN_HEIGHT, i, scene, 0x87CEEBFF);
		i++;
	}
	i = scene.player->central_angle + WIN_HEIGHT / 2 - scene.player->is_crouching;
	while (i < WIN_HEIGHT)
	{
		drawline(0 , i, WIN_HEIGHT, i, scene, 0x9b7653FF);
		i++;
	}
	ray_caster(&scene);
	i = 0;
	while (i < scene.sprite_count)
	{
		scene.sprites[i]->sprite_distance = sqrt(pow(scene.sprites[i]->pos[Y] - scene.player->pos[Y], 2) + pow(scene.sprites[i]->pos[X] - scene.player->pos[X], 2));
		i++;
	}
	sort_sprites(scene.sprites, scene.sprite_count);
	i = 0;
	while (i < scene.sprite_count)
	{
		spawn_sprites(&scene, i);
		i++;
	}

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
	mlx_put_pixel(scene.mlx_img, scene.player->pos[Y] / 5, scene.player->pos[X] / 5, 0xFF0000FF);
	mlx_put_pixel(scene.mlx_img, (scene.player->pos[Y] + scene.player->dir[Y]) / 5, (scene.player->pos[X] + scene.player->dir[X]) / 5, 0xFF0000FF);
	drawline(scene.player->pos[Y] / 5, scene.player->pos[X] / 5, (scene.player->pos[Y] + scene.player->dir[Y]) / 5, (scene.player->pos[X] + scene.player->dir[X]) / 5, scene, 0x00FF00FF);
	drawline((scene.player->pos[Y] + scene.player->dir[Y]) / 5, (scene.player->pos[X] + scene.player->dir[X]) / 5, (scene.player->pos[Y] + scene.player->dir[Y] + scene.player->plane[Y]) / 5, (scene.player->pos[X] + scene.player->dir[X] + scene.player->plane[X]) / 5, scene, 0x0000FFFF);
	drawline((scene.player->pos[Y] + scene.player->dir[Y]) / 5, (scene.player->pos[X] + scene.player->dir[X]) / 5, (scene.player->pos[Y] + scene.player->dir[Y] - scene.player->plane[Y]) / 5, (scene.player->pos[X] + scene.player->dir[X] - scene.player->plane[X]) / 5, scene, 0x0000FFFF);
	drawbar(scene);
	if (scene.player->is_ded == TRUE)
	{
		// i = 2 * WIN_HEIGHT / 5;
		// while (i < WIN_HEIGHT - 2 * WIN_HEIGHT / 5)
		// {
		// 	j = 0;
		// 	while (j < WIN_WIDTH)
		// 	{
		// 		if (i % 3 != 0 || j % 3 != 0)
		// 			mlx_put_pixel(scene.mlx_img, j, i, 0x00000000);
		// 		j++;
		// 	}
		// 	i++;
		// }
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 00:46:52 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/06 20:08:51 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdio.h>

void	gameloop(void *scene2)
{
	t_scene	*scene;
	scene = (t_scene *)scene2;
	mlx_delete_image(scene->mlx_ptr, scene->mlx_img);
	scene->mlx_img = mlx_new_image(scene->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	scene->oldtime = scene->time;
	scene->time = mlx_get_time();
	scene->frame_time = (scene->time - scene->oldtime);
	printf("FPS: %f\n", 1 / scene->frame_time);
	if (scene->player->forward)
	{
		double delta_x = scene->player->dir[Y] * scene->move_speed;
		double delta_y = scene->player->dir[X] * scene->move_speed;
		if (scene->map->map[(int)(scene->player->pos[X]) / UNIT][(int)(scene->player->pos[Y] + delta_x) / (UNIT)] != '1' && !does_it_collide(scene, 1))
			scene->player->pos[Y] += delta_x;
		if (scene->map->map[(int)(scene->player->pos[X] + delta_y) / (UNIT)][(int)(scene->player->pos[Y]) / UNIT] != '1' && !does_it_collide(scene, 2))
			scene->player->pos[X] += delta_y;
	}
	if (scene->player->backwards)
	{
		if (scene->map->map[(int)(scene->player->pos[X]) / UNIT][(int)(scene->player->pos[Y] - scene->player->dir[Y] * scene->move_speed) / (UNIT)] != '1' && !does_it_collide(scene, 3))
			scene->player->pos[Y] -= scene->player->dir[Y] * scene->move_speed;
		if (scene->map->map[(int)(scene->player->pos[X] - scene->player->dir[X] * scene->move_speed) / (UNIT)][(int)(scene->player->pos[Y]) / UNIT] != '1' && !does_it_collide(scene, 4))
			scene->player->pos[X] -= scene->player->dir[X] * scene->move_speed;
	}
	if (scene->player->left)
	{
		if (scene->map->map[(int)(scene->player->pos[X]) / UNIT][(int)(scene->player->pos[Y] - scene->player->plane[Y] * scene->move_speed) / (UNIT)] != '1' && !does_it_collide(scene, 5))
			scene->player->pos[Y] -= scene->player->plane[Y] * scene->move_speed;
		if (scene->map->map[(int)(scene->player->pos[X] - scene->player->plane[X] * scene->move_speed) / (UNIT)][(int)(scene->player->pos[Y]) / UNIT] != '1' && !does_it_collide(scene, 6))
			scene->player->pos[X] -= scene->player->plane[X] * scene->move_speed;
	}
	if (scene->player->right)
	{
		if (scene->map->map[(int)(scene->player->pos[X]) / UNIT][(int)(scene->player->pos[Y] + scene->player->plane[Y] * scene->move_speed) / (UNIT)] != '1' && !does_it_collide(scene, 7))
			scene->player->pos[Y] += scene->player->plane[Y] * scene->move_speed;
		if (scene->map->map[(int)(scene->player->pos[X] + scene->player->plane[X] * scene->move_speed) / (UNIT)][(int)(scene->player->pos[Y]) / UNIT] != '1' && !does_it_collide(scene, 8))
			scene->player->pos[X] += scene->player->plane[X] * scene->move_speed;
	}
	if (scene->player->is_trapped)
	{
		scene->damaged_time = mlx_get_time();
		if (scene->player->is_trapped == 1.00)
		{
			scene->old_damaged_time = scene->damaged_time;
			if (scene->player->health_points - 10 < 0)
				scene->player->health_points = 0;
			else
				scene->player->health_points -= 10;
		}
		if (scene->damaged_time - scene->old_damaged_time > 1)
		{
			if (scene->player->health_points - 10 < 0)
				scene->player->health_points = 0;
			else
				scene->player->health_points -= 10;
			scene->old_damaged_time = scene->damaged_time;
		}
	}
	projectile_logic(scene);
	if (1 / scene->frame_time < 40)
		scene->frame_time = 1 / 40.0;
	dynamic_logic(scene);
	renderitall(*scene);
	scene->move_speed = scene->frame_time * 5 * scene->player->velocity;
}

int	main(int argc, char *argv[])
{
	t_scene		scene;
	scene.map = ft_calloc(sizeof(t_map), 1);
	if (argc != 2)
		return (1);
	if (parser(argv[1], scene.map))
	{
		printf("ERROR\n");
		return (1);
	}

	printf("ceiling: %d,%d,%d\n", scene.map->ceiling_rgb[0], scene.map->ceiling_rgb[1], scene.map->ceiling_rgb[2]);
	printf("floor: %d,%d,%d\n", scene.map->floor_rgb[0], scene.map->floor_rgb[1], scene.map->floor_rgb[2]);

	for (int i = 0; scene.map->map[i]; i++)
	{
		printf(">> [%s] <<\n", scene.map->map[i]);
	}

	printf("map props: %d,%d\n", scene.map->map_width, scene.map->map_height);
	scene.projectiles = NULL;
	allocat_player(&scene);
	scene.mlx_ptr = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Escape From GunDalf", 1);
	if (load_textures(scene.mlx_ptr, scene.map))
		return (1);
	initsprites(&scene);
	scene.time = 0;
	scene.mlx_img = mlx_new_image(scene.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx_loop_hook(scene.mlx_ptr, gameloop, &scene);
	mlx_set_cursor_mode(scene.mlx_ptr, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(scene.mlx_ptr, hookercur, &scene);
	mlx_key_hook(scene.mlx_ptr, hooker, &scene);
	mlx_loop(scene.mlx_ptr);
	return (0);
}

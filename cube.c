/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 00:46:52 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/26 04:44:10 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int map[11][10] = {{'0', '1', '1', '1', '1', '1', '1', '1', '1', '0'},
					{'1', 'N', '0', '0', '1', '1', '0', '0', '0', '1'},
					{'1', '0', '0', 'B', 'B', '1', '0', '0', '0', '1'},
					{'1', '0', '0', 'B', 'B', '1', '0', '0', '0', '1'},
					{'1', 'B', '1', '1', '1', '1', '1', '1', '0', '1'},
					{'1', '0', 'T', 'T', 'T', 'T', 'T', 'T', '0', '1'},
					{'1', '0', '1', '1', '1', '1', '1', '1', '0', '1'},
					{'1', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
					{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};

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
				scene->player->pos[Y] = j * WIN_WIDTH / scene->map->map_height + WIN_WIDTH / scene->map->map_height / 2;
				scene->player->pos[X] = i * WIN_HEIGHT / scene->map->map_width + WIN_HEIGHT / scene->map->map_width / 2;
			}
			j++;
		}
		i++;
	}
	scene->player->p_angle = 0;
	scene->player->dir[Y] = (double)cosf(scene->player->p_angle) * 25;
	scene->player->dir[X] = (double)sinf(scene->player->p_angle) * 25;
	scene->player->plane[Y] = (double)cosf(scene->player->p_angle + M_PI / 2) * 16.5;
	scene->player->plane[X] = (double)sinf(scene->player->p_angle + M_PI / 2) * 16.5;
	scene->player->health_points = 100;
	scene->player->mana_points = 100;
	scene->player->central_angle = 0;
	scene->player->is_ded = FALSE;
	scene->player->forward = FALSE;
	scene->player->backwards = FALSE;
	scene->player->left = FALSE;
	scene->player->right = FALSE;
	scene->player->is_running = 1;
	scene->player->is_jumping = FALSE;
	scene->player->is_trapped = FALSE;
	scene->player->is_crouching = FALSE;

}

void	dynamic_logic(t_scene *scene)
{
	int height = WIN_HEIGHT / scene->map->map_width;
	int width = WIN_WIDTH / scene->map->map_height;
	if (scene->player->health_points <= 0)
		scene->player->is_ded = TRUE;
	if (map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y]) / height] == 'T' && scene->player->health_points > 0)
		scene->player->is_trapped += TRUE;
	else
		scene->player->is_trapped = FALSE;
}

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
	int height = WIN_HEIGHT / scene->map->map_width;
	int width = WIN_WIDTH / scene->map->map_height;
	if (scene->player->forward)
	{
		double delta_x = scene->player->dir[Y] * scene->move_speed;
		double delta_y = scene->player->dir[X] * scene->move_speed;
		if (map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y] + delta_x) / (WIN_WIDTH / scene->map->map_height)] != '1')
			scene->player->pos[Y] += delta_x;
		if (map[(int)(scene->player->pos[X] + delta_y) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[Y]) / height] != '1')
			scene->player->pos[X] += delta_y;
	}
	if (scene->player->backwards)
	{
		if (map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y] - scene->player->dir[Y] / 1.5) / (WIN_WIDTH / scene->map->map_height)] != '1')
			scene->player->pos[Y] -= scene->player->dir[Y] * scene->move_speed;
		if (map[(int)(scene->player->pos[X] - scene->player->dir[X] / 1.5) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[Y]) / height] != '1')
			scene->player->pos[X] -= scene->player->dir[X] * scene->move_speed;
	}
	if (scene->player->left)
	{
		if (map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y] - scene->player->plane[Y] / 1.5) / (WIN_WIDTH / scene->map->map_height)] != '1')
			scene->player->pos[Y] -= scene->player->plane[Y] * scene->move_speed;
		if (map[(int)(scene->player->pos[X] - scene->player->plane[X] / 1.5) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[Y]) / height] != '1')
			scene->player->pos[X] -= scene->player->plane[X] * scene->move_speed;
	}
	if (scene->player->right)
	{
		if (map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y] + scene->player->plane[Y] / 1.5) / (WIN_WIDTH / scene->map->map_height)] != '1')
			scene->player->pos[Y] += scene->player->plane[Y] * scene->move_speed;
		if (map[(int)(scene->player->pos[X] + scene->player->plane[X] / 1.5) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[Y]) / height] != '1')
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
	if (1 / scene->frame_time < 30)
		scene->frame_time = 1 / 30.0;
	dynamic_logic(scene);
	renderitall(*scene);
	scene->move_speed = scene->frame_time * 5 * scene->player->is_running;
}

int	main()
{
	t_scene		scene;
	scene.map = malloc(sizeof(t_map));
	scene.map->map_width = 11;
	scene.map->map_height = 10;
	initplayer(&scene);
	scene.mlx_ptr = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Escape From GunDalf", 1);
	scene.time = 0;
	scene.mlx_img = mlx_new_image(scene.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx_loop_hook(scene.mlx_ptr, gameloop, &scene);
	mlx_set_cursor_mode(scene.mlx_ptr, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(scene.mlx_ptr, hookercur, &scene);
	mlx_key_hook(scene.mlx_ptr, hooker, &scene);
	mlx_loop(scene.mlx_ptr);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GunDalf <GunDalf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 00:46:52 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/27 05:27:07 by GunDalf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int map[11][10] = {{'0', '1', '1', '1', '1', '1', '1', '1', '1', '0'},
					{'1', 'N', '0', '0', 'P', '1', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
					{'1', '0', '0', '0', '0', '0', '1', '1', '0', '1'},
					{'1', '0', 'T', 'T', 'T', 'T', 'T', 'T', '0', '1'},
					{'1', 'B', '0', '0', '1', '1', '1', '1', '0', '1'},
					{'1', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
					{'1', 'B', '1', '0', '0', '0', '0', '0', '0', '1'},
					{'1', 'P', '0', '0', '0', '0', '0', 'P', 'P', '1'},
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
	scene->player->will_collide[Y] = FALSE;
	scene->player->will_collide[X] = FALSE;
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

int	does_it_collide(t_scene *scene, int cas)
{
	int i = 0;

	while (i < scene->sprite_count)
	{
		printf("sprite distance: %f\n", scene->sprites[i]->sprite_distance);
		if (cas == 1 && scene->sprites[i]->sprite_distance - scene->player->dir[Y] * 1.5 <= scene->sprites[i]->collision_box)
			return (TRUE);
		if (cas == 2 && scene->sprites[i]->sprite_distance - scene->player->dir[X] * 1.5 <= scene->sprites[i]->collision_box)
			return (TRUE);
		if (cas == 3 && scene->sprites[i]->sprite_distance + scene->player->dir[Y] * 1.5 <= scene->sprites[i]->collision_box)
			return (TRUE);
		if (cas == 4 && scene->sprites[i]->sprite_distance + scene->player->dir[X] * 1.5 <= scene->sprites[i]->collision_box)
			return (TRUE);
		if (cas == 5 && scene->sprites[i]->sprite_distance - scene->player->plane[Y] * 1.5 <= scene->sprites[i]->collision_box)
			return (TRUE);
		if (cas == 6 && scene->sprites[i]->sprite_distance - scene->player->plane[X] * 1.5 <= scene->sprites[i]->collision_box)
			return (TRUE);
		if (cas == 7 && scene->sprites[i]->sprite_distance + scene->player->plane[Y] * 1.5 <= scene->sprites[i]->collision_box)
			return (TRUE);
		if (cas == 8 && scene->sprites[i]->sprite_distance + scene->player->plane[X] * 1.5 <= scene->sprites[i]->collision_box)
			return (TRUE);
		i++;
	}
	return (FALSE);
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
		if (map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y] + delta_x) / (WIN_WIDTH / scene->map->map_height)] != '1' && map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y] + delta_x) / (WIN_WIDTH / scene->map->map_height)] != 'B' && map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y] + delta_x) / (WIN_WIDTH / scene->map->map_height)] != 'P')
			scene->player->pos[Y] += delta_x;
		if (map[(int)(scene->player->pos[X] + delta_y) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[Y]) / height] != '1' && map[(int)(scene->player->pos[X] + delta_y) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[Y]) / height] != 'B' && map[(int)(scene->player->pos[X] + delta_y) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[Y]) / height] != 'P')
			scene->player->pos[X] += delta_y;
	}
	if (scene->player->backwards)
	{
		if (map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y] - scene->player->dir[Y] * scene->move_speed) / (WIN_WIDTH / scene->map->map_height)] != '1' && map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y] - scene->player->dir[Y] * scene->move_speed) / (WIN_WIDTH / scene->map->map_height)] != 'B' && map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y] - scene->player->dir[Y] * scene->move_speed) / (WIN_WIDTH / scene->map->map_height)] != 'P')
			scene->player->pos[Y] -= scene->player->dir[Y] * scene->move_speed;
		if (map[(int)(scene->player->pos[X] - scene->player->dir[X] * scene->move_speed) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[Y]) / height] != '1' && map[(int)(scene->player->pos[X] - scene->player->dir[X] * scene->move_speed) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[Y]) / height] != 'B' && map[(int)(scene->player->pos[X] - scene->player->dir[X] * scene->move_speed) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[Y]) / height] != 'P')
			scene->player->pos[X] -= scene->player->dir[X] * scene->move_speed;
	}
	if (scene->player->left)
	{
		if (map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y] - scene->player->plane[Y] * scene->move_speed) / (WIN_WIDTH / scene->map->map_height)] != '1' && map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y] - scene->player->plane[Y] * scene->move_speed) / (WIN_WIDTH / scene->map->map_height)] != 'B' && map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y] - scene->player->plane[Y] * scene->move_speed) / (WIN_WIDTH / scene->map->map_height)] != 'P')
			scene->player->pos[Y] -= scene->player->plane[Y] * scene->move_speed;
		if (map[(int)(scene->player->pos[X] - scene->player->plane[X] * scene->move_speed) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[Y]) / height] != '1' && map[(int)(scene->player->pos[X] - scene->player->plane[X] * scene->move_speed) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[Y]) / height] != 'B' && map[(int)(scene->player->pos[X] - scene->player->plane[X] * scene->move_speed) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[Y]) / height] != 'P')
			scene->player->pos[X] -= scene->player->plane[X] * scene->move_speed;
	}
	if (scene->player->right)
	{
		if (map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y] + scene->player->plane[Y] * scene->move_speed) / (WIN_WIDTH / scene->map->map_height)] != '1' && map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y] + scene->player->plane[Y] * scene->move_speed) / (WIN_WIDTH / scene->map->map_height)] != 'B' && map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y] + scene->player->plane[Y] * scene->move_speed) / (WIN_WIDTH / scene->map->map_height)] != 'P')
			scene->player->pos[Y] += scene->player->plane[Y] * scene->move_speed;
		if (map[(int)(scene->player->pos[X] + scene->player->plane[X] * scene->move_speed) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[Y]) / height] != '1' && map[(int)(scene->player->pos[X] + scene->player->plane[X] * scene->move_speed) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[Y]) / height] != 'B' && map[(int)(scene->player->pos[X] + scene->player->plane[X] * scene->move_speed) / (WIN_HEIGHT / scene->map->map_width)][(int)(scene->player->pos[Y]) / height] != 'P')
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
	if (1 / scene->frame_time < 40)
		scene->frame_time = 1 / 40.0;
	dynamic_logic(scene);
	renderitall(*scene);
	scene->move_speed = scene->frame_time * 5 * scene->player->is_running;
}

void	set_sprites_up(t_scene *scene, int i, int j, int count)
{
	scene->sprites[count]->pos[Y] = j * WIN_WIDTH / scene->map->map_height + WIN_WIDTH / scene->map->map_height / 2;
	scene->sprites[count]->pos[X] = i * WIN_HEIGHT / scene->map->map_width + WIN_HEIGHT / scene->map->map_width / 2;
}

void	initsprites(t_scene *scene)
{
	int	i;
	int	count;
	int	j;

	i = 0;
	count = 0;
	scene->barrel_tex = mlx_load_png("./barrel_01.png");
	scene->barrel_img = mlx_texture_to_image(scene->mlx_ptr, scene->barrel_tex);
	mlx_resize_image(scene->barrel_img, 415, 250);
	mlx_delete_texture(scene->barrel_tex);
	scene->pillar_tex = mlx_load_png("./Pillar.png");
	scene->pillar_img = mlx_texture_to_image(scene->mlx_ptr, scene->pillar_tex);
	mlx_resize_image(scene->pillar_img, 500, 500);
	mlx_delete_texture(scene->pillar_tex);
	while (i < scene->map->map_width)
	{
		j = 0;
		while (j < scene->map->map_height)
		{
			if (map[i][j] == 'B')
				count++;
			if (map[i][j] == 'P')
				count++;
			j++;
		}
		i++;
	}
	scene->sprite_count = count;
	scene->sprites = ft_calloc(count, sizeof(t_sprite *));
	i = 0;
	count = 0;
	while (i < scene->map->map_width)
	{
		j = 0;
		while (j < scene->map->map_height)
		{
			if (map[i][j] == 'B')
			{
				scene->sprites[count] = ft_calloc(1, sizeof(t_sprite));
				scene->sprites[count]->sprite_img = scene->barrel_img ;
				scene->sprites[count]->v_move = 1100;
				scene->sprites[count]->collision_box = 50;
				set_sprites_up(scene, i, j, count);
				count++;
			}
			if (map[i][j] == 'P')
			{
				scene->sprites[count] = ft_calloc(1, sizeof(t_sprite));
				scene->sprites[count]->sprite_img = scene->pillar_img;
				scene->sprites[count]->v_move = 50;
				set_sprites_up(scene, i, j, count);
				count++;
			}
			j++;
		}
		i++;
	}
}

int	main()
{
	t_scene		scene;
	scene.map = malloc(sizeof(t_map));
	scene.map->map_width = 11;
	scene.map->map_height = 10;
	initplayer(&scene);
	scene.mlx_ptr = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Escape From GunDalf", 1);
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
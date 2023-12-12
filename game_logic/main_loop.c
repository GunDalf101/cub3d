/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:28:49 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/12 22:51:19 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	rotate_left(t_scene *scene)
{
	scene->player->p_angle -= 0.2;
	if (scene->player->p_angle > 2 * M_PI)
		scene->player->p_angle -= 2 * M_PI;
	else if (scene->player->p_angle < 0)
		scene->player->p_angle += 2 * M_PI;
	scene->player->dir[Y] = (double)cosf(scene->player->p_angle) * 25;
	scene->player->dir[X] = (double)sinf(scene->player->p_angle) * 25;
	scene->player->plane[Y] = (double)cosf(scene->player->p_angle + M_PI / 2)
		* 16.5;
	scene->player->plane[X] = (double)sinf(scene->player->p_angle + M_PI / 2)
		* 16.5;
}

void	rotate_right(t_scene *scene)
{
	scene->player->p_angle += 0.2;
	if (scene->player->p_angle < 0)
		scene->player->p_angle += 2 * M_PI;
	else if (scene->player->p_angle > 2 * M_PI)
		scene->player->p_angle -= 2 * M_PI;
	scene->player->dir[Y] = (double)cosf(scene->player->p_angle) * 25;
	scene->player->dir[X] = (double)sinf(scene->player->p_angle) * 25;
	scene->player->plane[Y] = (double)cosf(scene->player->p_angle + M_PI / 2)
		* 16.5;
	scene->player->plane[X] = (double)sinf(scene->player->p_angle + M_PI / 2)
		* 16.5;
}

void	movement_logic(t_scene *scene)
{
	if (scene->player->forward)
		move_forward(scene);
	if (scene->player->backwards)
		move_backward(scene);
	if (scene->player->left)
		move_left(scene);
	if (scene->player->right)
		move_right(scene);
	if (scene->player->rot_left)
		rotate_left(scene);
	if (scene->player->rot_right)
		rotate_right(scene);
}

void	trap_logic(t_scene *scene)
{
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
}

void	gameloop(void *scene2)
{
	t_scene	*scene;

	scene = (t_scene *)scene2;
	check_pole(scene);
	check_enemy_state(scene);
	state_machine(scene);
	mlx_delete_image(scene->mlx_ptr, scene->mlx_img);
	scene->mlx_img = mlx_new_image(scene->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	scene->oldtime = scene->time;
	scene->time = mlx_get_time();
	scene->frame_time = (scene->time - scene->oldtime);
	movement_logic(scene);
	trap_logic(scene);
	projectile_logic(scene);
	if (1 / scene->frame_time < 40)
		scene->frame_time = 1 / 40.0;
	dynamic_logic(scene);
	renderitall(*scene);
	scene->move_speed = scene->frame_time * 5 * scene->player->velocity;
}

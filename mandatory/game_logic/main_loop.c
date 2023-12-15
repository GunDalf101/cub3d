/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:28:49 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/15 11:59:51 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	rotate_left(t_scene *scene)
{
	scene->player->p_angle -= 0.1;
	if (scene->player->p_angle > 2 * M_PI)
		scene->player->p_angle -= 2 * M_PI;
	else if (scene->player->p_angle < 0)
		scene->player->p_angle += 2 * M_PI;
	scene->player->dir[Y] = (double)cos(scene->player->p_angle) * 25;
	scene->player->dir[X] = (double)sin(scene->player->p_angle) * 25;
	scene->player->plane[Y] = (double)cos(scene->player->p_angle + M_PI / 2)
		* 16.5;
	scene->player->plane[X] = (double)sin(scene->player->p_angle + M_PI / 2)
		* 16.5;
}

void	rotate_right(t_scene *scene)
{
	scene->player->p_angle += 0.1;
	if (scene->player->p_angle < 0)
		scene->player->p_angle += 2 * M_PI;
	else if (scene->player->p_angle > 2 * M_PI)
		scene->player->p_angle -= 2 * M_PI;
	scene->player->dir[Y] = (double)cos(scene->player->p_angle) * 25;
	scene->player->dir[X] = (double)sin(scene->player->p_angle) * 25;
	scene->player->plane[Y] = (double)cos(scene->player->p_angle + M_PI / 2)
		* 16.5;
	scene->player->plane[X] = (double)sin(scene->player->p_angle + M_PI / 2)
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
	movement_logic(scene);
	if (1 / scene->frame_time < 40)
		scene->frame_time = 1 / 40.0;
	renderitall(*scene);
	scene->move_speed = scene->frame_time * 5 * scene->player->velocity;
}

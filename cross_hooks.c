/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:24:50 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/26 04:02:14 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

extern int map[11][10];

void	hooker(mlx_key_data_t keycode, void *scene2)
{
	t_scene	*scene;
	scene = (t_scene *)scene2;
	scene->key_data = keycode;
	if (keycode.key == MLX_KEY_ESCAPE)
		exit(0);
	if (keycode.key == MLX_KEY_W && keycode.action == MLX_PRESS)
		scene->player->forward = TRUE;
	else if (keycode.key == MLX_KEY_W && keycode.action == MLX_RELEASE)
		scene->player->forward = FALSE;
	if (keycode.key == MLX_KEY_S && keycode.action == MLX_PRESS)
		scene->player->backwards = TRUE;
	else if (keycode.key == MLX_KEY_S && keycode.action == MLX_RELEASE)
		scene->player->backwards = FALSE;
	if (keycode.key == MLX_KEY_A && keycode.action == MLX_PRESS)
		scene->player->left = TRUE;
	else if (keycode.key == MLX_KEY_A && keycode.action == MLX_RELEASE)
		scene->player->left = FALSE;
	if (keycode.key == MLX_KEY_D && keycode.action == MLX_PRESS)
		scene->player->right = TRUE;
	else if (keycode.key == MLX_KEY_D && keycode.action == MLX_RELEASE)
		scene->player->right = FALSE;
	if (keycode.key == MLX_KEY_LEFT_SHIFT && keycode.action == MLX_PRESS)
		scene->player->is_running = 3;
	else if (keycode.key == MLX_KEY_LEFT_SHIFT && keycode.action == MLX_RELEASE)
		scene->player->is_running = 1.5;
	if (keycode.key == MLX_KEY_LEFT_CONTROL && keycode.action == MLX_PRESS)
	{
		scene->player->is_crouching = 50;
		scene->player->is_running = 0.75;
	}
	else if (keycode.key == MLX_KEY_LEFT_CONTROL && keycode.action == MLX_RELEASE)
	{
		scene->player->is_crouching = FALSE;
		scene->player->is_running = 1.5;
	}
	if (keycode.key == MLX_KEY_SPACE && keycode.action == MLX_PRESS)
		scene->player->is_jumping = TRUE;
	else if (keycode.key == MLX_KEY_SPACE && keycode.action == MLX_RELEASE)
		scene->player->is_running = FALSE;
	if (keycode.key == MLX_KEY_LEFT)
	{
		scene->player->p_angle -= 0.1;
		if (scene->player->p_angle > 2 * M_PI)
			scene->player->p_angle -= 2 * M_PI;
		scene->player->dir[Y] = (double)cosf(scene->player->p_angle) * 25;
		scene->player->dir[X] = (double)sinf(scene->player->p_angle) * 25;
		scene->player->plane[Y] = (double)cosf(scene->player->p_angle + M_PI / 2) * 16.5;
		scene->player->plane[X] = (double)sinf(scene->player->p_angle + M_PI / 2) * 16.5;
	}
	if (keycode.key == MLX_KEY_RIGHT)
	{
		scene->player->p_angle += 0.1;
		if (scene->player->p_angle < 0)
			scene->player->p_angle += 2 * M_PI;
		scene->player->dir[Y] = (double)cosf(scene->player->p_angle) * 25;
		scene->player->dir[X] = (double)sinf(scene->player->p_angle) * 25;
		scene->player->plane[Y] = (double)cosf(scene->player->p_angle + M_PI / 2) * 16.5;
		scene->player->plane[X] = (double)sinf(scene->player->p_angle + M_PI / 2) * 16.5;
	}
	if (keycode.key == MLX_KEY_E && scene->player->mana_points >= 20 && scene->player->health_points > 0 && scene->player->health_points < 100 && keycode.action == 1)
	{
		scene->player->mana_points -= 20;
		if (scene->player->health_points + 20 > 100)
			scene->player->health_points = 100;
		else
			scene->player->health_points += 20;
	}
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
	if (scene->player->central_angle > WIN_HEIGHT / 2)
		scene->player->central_angle = WIN_HEIGHT / 2;
	if (scene->player->central_angle < -WIN_HEIGHT / 3)
		scene->player->central_angle = -WIN_HEIGHT / 3;
	scene->player->dir[Y] = (double)cosf(scene->player->p_angle) * 25;
	scene->player->dir[X] = (double)sinf(scene->player->p_angle) * 25;
	scene->player->plane[Y] = (double)cosf(scene->player->p_angle + M_PI / 2) * 16.5;
	scene->player->plane[X] = (double)sinf(scene->player->p_angle + M_PI / 2) * 16.5;
	old_ypos = ypos;
}
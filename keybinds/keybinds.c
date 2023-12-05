/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:37:36 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/05 15:05:27 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	player_movement(mlx_key_data_t keycode, t_scene *scene)
{
	if (keycode.key == MLX_KEY_W && keycode.action == MLX_PRESS
		&& scene->player->is_ded == FALSE)
		scene->player->forward = TRUE;
	else if (keycode.key == MLX_KEY_W && keycode.action == MLX_RELEASE)
		scene->player->forward = FALSE;
	if (keycode.key == MLX_KEY_S && keycode.action == MLX_PRESS
		&& scene->player->is_ded == FALSE)
		scene->player->backwards = TRUE;
	else if (keycode.key == MLX_KEY_S && keycode.action == MLX_RELEASE)
		scene->player->backwards = FALSE;
	if (keycode.key == MLX_KEY_A && keycode.action == MLX_PRESS
		&& scene->player->is_ded == FALSE)
		scene->player->left = TRUE;
	else if (keycode.key == MLX_KEY_A && keycode.action == MLX_RELEASE)
		scene->player->left = FALSE;
	if (keycode.key == MLX_KEY_D && keycode.action == MLX_PRESS
		&& scene->player->is_ded == FALSE)
		scene->player->right = TRUE;
	else if (keycode.key == MLX_KEY_D && keycode.action == MLX_RELEASE)
		scene->player->right = FALSE;
}

void	velocity_keys(mlx_key_data_t keycode, t_scene *scene)
{
	if (keycode.key == MLX_KEY_LEFT_SHIFT && keycode.action == MLX_PRESS
		&& scene->player->is_ded == FALSE
		&& scene->player->crouch == FALSE)
		scene->player->velocity = 3;
	else if (keycode.key == MLX_KEY_LEFT_SHIFT && keycode.action == MLX_RELEASE)
		scene->player->velocity = 1.5;
	if (keycode.key == MLX_KEY_LEFT_CONTROL && keycode.action == MLX_PRESS
		&& scene->player->is_ded == FALSE)
	{
		scene->player->crouch = 75;
		scene->player->velocity = 0.75;
	}
	else if (keycode.key == MLX_KEY_LEFT_CONTROL
		&& keycode.action == MLX_RELEASE && scene->player->is_ded == FALSE)
	{
		scene->player->crouch = FALSE;
		scene->player->velocity = 1.5;
	}
}

void	spells_keys(mlx_key_data_t keycode, t_scene *scene)
{
	if (keycode.key == MLX_KEY_E && scene->player->mana_points >= 20
		&& scene->player->health_points > 0
		&& scene->player->health_points < 100 && keycode.action == 1)
	{
		system("afplay assets/Heal.mp3 &");
		scene->player->mana_points -= 20;
		if (scene->player->health_points + 20 > 100)
			scene->player->health_points = 100;
		else
			scene->player->health_points += 20;
	}
	if (keycode.key == MLX_KEY_1 && keycode.action == MLX_RELEASE
		&& scene->player->is_ded == FALSE && scene->player->mana_points >= 5)
	{
		system("afplay assets/FireBall.mp3 &");
		scene->player->mana_points -= 5;
		add_projectile(scene, FIREBALL);
	}
	if (keycode.key == MLX_KEY_2 && keycode.action == MLX_RELEASE
		&& scene->player->is_ded == FALSE && scene->player->mana_points >= 5)
	{
		system("afplay assets/IceOrb.mp3 &");
		scene->player->mana_points -= 5;
		add_projectile(scene, ICEBALL);
	}
}

void	hooker(mlx_key_data_t keycode, void *scene2)
{
	t_scene	*scene;

	scene = (t_scene *)scene2;
	scene->key_data = keycode;
	if (keycode.key == MLX_KEY_ESCAPE)
		exit(0);
	player_movement(keycode, scene);
	velocity_keys(keycode, scene);
	if (keycode.key == MLX_KEY_SPACE && keycode.action == MLX_PRESS)
		scene->player->is_jumping = TRUE;
	else if (keycode.key == MLX_KEY_SPACE && keycode.action == MLX_RELEASE)
		scene->player->is_jumping = FALSE;
	// if (keycode.key == MLX_KEY_LEFT)
	// {
	// 	scene->player->p_angle -= 0.1;
	// 	if (scene->player->p_angle > 2 * M_PI)
	// 		scene->player->p_angle -= 2 * M_PI;
	// 	scene->player->dir[Y] = (double)cosf(scene->player->p_angle) * 25;
	// 	scene->player->dir[X] = (double)sinf(scene->player->p_angle) * 25;
	// 	scene->player->plane[Y] = (double)cosf(scene->player->p_angle + M_PI
	// 			/ 2) * 16.5;
	// 	scene->player->plane[X] = (double)sinf(scene->player->p_angle + M_PI
	// 			/ 2) * 16.5;
	// }
	// if (keycode.key == MLX_KEY_RIGHT)
	// {
	// 	scene->player->p_angle += 0.1;
	// 	if (scene->player->p_angle < 0)
	// 		scene->player->p_angle += 2 * M_PI;
	// 	scene->player->dir[Y] = (double)cosf(scene->player->p_angle) * 25;
	// 	scene->player->dir[X] = (double)sinf(scene->player->p_angle) * 25;
	// 	scene->player->plane[Y] = (double)cosf(scene->player->p_angle + M_PI
	// 			/ 2) * 16.5;
	// 	scene->player->plane[X] = (double)sinf(scene->player->p_angle + M_PI
	// 			/ 2) * 16.5;
	// }
	spells_keys(keycode, scene);
}

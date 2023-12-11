/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:37:36 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/11 13:23:38 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	player_movement(mlx_key_data_t keycode, t_scene *scene)
{
	if (keycode.key == MLX_KEY_W && keycode.action == MLX_PRESS
		&& !scene->player->is_ded && !scene->win)
		scene->player->forward = TRUE;
	else if ((keycode.key == MLX_KEY_W && keycode.action == MLX_RELEASE)
		|| scene->player->is_ded || scene->win)
		scene->player->forward = FALSE;
	if (keycode.key == MLX_KEY_S && keycode.action == MLX_PRESS
		&& !scene->player->is_ded && !scene->win)
		scene->player->backwards = TRUE;
	else if ((keycode.key == MLX_KEY_S && keycode.action == MLX_RELEASE)
		|| scene->player->is_ded || scene->win)
		scene->player->backwards = FALSE;
	if (keycode.key == MLX_KEY_A && keycode.action == MLX_PRESS
		&& !scene->player->is_ded && !scene->win)
		scene->player->left = TRUE;
	else if ((keycode.key == MLX_KEY_A && keycode.action == MLX_RELEASE)
		|| scene->player->is_ded || scene->win)
		scene->player->left = FALSE;
	if (keycode.key == MLX_KEY_D && keycode.action == MLX_PRESS
		&& !scene->player->is_ded && !scene->win)
		scene->player->right = TRUE;
	else if ((keycode.key == MLX_KEY_D && keycode.action == MLX_RELEASE)
		|| scene->player->is_ded || scene->win)
		scene->player->right = FALSE;
}

void	velocity_keys(mlx_key_data_t keycode, t_scene *scene)
{
	if (keycode.key == MLX_KEY_LEFT_SHIFT && keycode.action == MLX_PRESS
		&& scene->player->crouch == FALSE)
		scene->player->velocity = 3;
	else if ((keycode.key == MLX_KEY_LEFT_SHIFT
			&& keycode.action == MLX_RELEASE) || scene->player->is_ded
		|| scene->win)
		scene->player->velocity = 1.5;
	if (keycode.key == MLX_KEY_LEFT_CONTROL && keycode.action == MLX_PRESS)
	{
		scene->player->crouch = 75;
		scene->player->velocity = 0.75;
	}
	else if ((keycode.key == MLX_KEY_LEFT_CONTROL
			&& keycode.action == MLX_RELEASE) || scene->player->is_ded
		|| scene->win)
	{
		scene->player->crouch = FALSE;
		scene->player->velocity = 1.5;
	}
	if (scene->player->is_ded || scene->win)
		scene->player->velocity = 0;
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
		&& scene->player->mana_points >= 5)
	{
		system("afplay assets/FireBall.mp3 &");
		scene->player->mana_points -= 5;
		add_projectile(scene, FIREBALL);
	}
	if (keycode.key == MLX_KEY_2 && keycode.action == MLX_RELEASE
		&& scene->player->mana_points >= 5)
	{
		system("afplay assets/IceOrb.mp3 &");
		scene->player->mana_points -= 5;
		add_projectile(scene, ICEBALL);
	}
}

void	player_rotation(mlx_key_data_t keycode, t_scene *scene)
{
	if (keycode.key == MLX_KEY_LEFT && keycode.action == MLX_PRESS
		&& !scene->player->is_ded && !scene->win)
		scene->player->rot_left = TRUE;
	else if ((keycode.key == MLX_KEY_LEFT && keycode.action == MLX_RELEASE)
		|| scene->player->is_ded || scene->win)
		scene->player->rot_left = FALSE;
	if (keycode.key == MLX_KEY_RIGHT && keycode.action == MLX_PRESS
		&& !scene->player->is_ded && !scene->win)
		scene->player->rot_right = TRUE;
	else if ((keycode.key == MLX_KEY_RIGHT && keycode.action == MLX_RELEASE)
		|| scene->player->is_ded || scene->win)
		scene->player->rot_right = FALSE;
}

void	hooker(mlx_key_data_t keycode, void *scene2)
{
	t_scene	*scene;

	scene = (t_scene *)scene2;
	scene->key_data = keycode;
	if (keycode.key == MLX_KEY_ESCAPE)
	{
		final_free(scene);
		exit(0);
	}
	player_movement(keycode, scene);
	player_rotation(keycode, scene);
	velocity_keys(keycode, scene);
	if (keycode.key == MLX_KEY_SPACE && keycode.action == MLX_PRESS)
		check_door(keycode, scene);
	spells_keys(keycode, scene);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:37:36 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/15 06:10:17 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	player_movement(mlx_key_data_t keycode, t_scene *scene)
{
	if (keycode.key == MLX_KEY_W && keycode.action == MLX_PRESS)
		scene->player->forward = TRUE;
	else if ((keycode.key == MLX_KEY_W && keycode.action == MLX_RELEASE))
		scene->player->forward = FALSE;
	if (keycode.key == MLX_KEY_S && keycode.action == MLX_PRESS)
		scene->player->backwards = TRUE;
	else if ((keycode.key == MLX_KEY_S && keycode.action == MLX_RELEASE))
		scene->player->backwards = FALSE;
	if (keycode.key == MLX_KEY_A && keycode.action == MLX_PRESS)
		scene->player->left = TRUE;
	else if ((keycode.key == MLX_KEY_A && keycode.action == MLX_RELEASE))
		scene->player->left = FALSE;
	if (keycode.key == MLX_KEY_D && keycode.action == MLX_PRESS)
		scene->player->right = TRUE;
	else if ((keycode.key == MLX_KEY_D && keycode.action == MLX_RELEASE))
		scene->player->right = FALSE;
}

void	velocity_keys(mlx_key_data_t keycode, t_scene *scene)
{
	if (keycode.key == MLX_KEY_LEFT_SHIFT && keycode.action == MLX_PRESS
		&& scene->player->crouch == FALSE)
		scene->player->velocity = 4;
	else if ((keycode.key == MLX_KEY_LEFT_SHIFT
			&& keycode.action == MLX_RELEASE) || scene->player->is_ded
		|| scene->win)
		scene->player->velocity = 2;
	if (keycode.key == MLX_KEY_LEFT_CONTROL && keycode.action == MLX_PRESS)
	{
		scene->player->crouch = 75;
		scene->player->velocity = 1;
	}
	else if ((keycode.key == MLX_KEY_LEFT_CONTROL
			&& keycode.action == MLX_RELEASE) || scene->player->is_ded
		|| scene->win)
	{
		scene->player->crouch = FALSE;
		scene->player->velocity = 2;
	}
	if (scene->player->is_ded || scene->win)
		scene->player->velocity = 0;
}

void	light_spell(mlx_key_data_t keycode, t_scene *scene)
{
	if (keycode.key == MLX_KEY_3 && keycode.action == MLX_REPEAT
		&& scene->player->mana_points >= 5)
	{
		scene->lit_time = mlx_get_time();
		scene->player->is_lit += TRUE;
		if (scene->player->is_lit == 1.00)
		{
			scene->old_lit_time = scene->lit_time;
			scene->light_multiplier = 0.2;
			scene->player->mana_points -= 5;
		}
		if (scene->lit_time - scene->old_lit_time > 1)
		{
			scene->old_lit_time = scene->lit_time;
			scene->player->mana_points -= 5;
		}
	}
	else if (keycode.key == MLX_KEY_3 && keycode.action == MLX_RELEASE)
	{
		scene->player->is_lit = FALSE;
		scene->light_multiplier = 0.5;
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
	light_spell(keycode, scene);
}

void	player_rotation(mlx_key_data_t keycode, t_scene *scene)
{
	if (keycode.key == MLX_KEY_LEFT && keycode.action == MLX_PRESS)
		scene->player->rot_left = TRUE;
	else if ((keycode.key == MLX_KEY_LEFT && keycode.action == MLX_RELEASE))
		scene->player->rot_left = FALSE;
	if (keycode.key == MLX_KEY_RIGHT && keycode.action == MLX_PRESS)
		scene->player->rot_right = TRUE;
	else if ((keycode.key == MLX_KEY_RIGHT && keycode.action == MLX_RELEASE))
		scene->player->rot_right = FALSE;
}

void	hooker(mlx_key_data_t keycode, void *scene2)
{
	t_scene	*scene;

	scene = (t_scene *)scene2;
	scene->key_data = keycode;
	if (keycode.key == MLX_KEY_ESCAPE)
	{
		system("pkill afplay &");
		final_free(scene);
		exit(0);
	}
	if (scene->win || scene->player->is_ded)
	{
		scene->player->forward = FALSE;
		scene->player->backwards = FALSE;
		scene->player->left = FALSE;
		scene->player->right = FALSE;
		return ;
	}
	player_movement(keycode, scene);
	player_rotation(keycode, scene);
	velocity_keys(keycode, scene);
	if (keycode.key == MLX_KEY_Q && keycode.action == MLX_PRESS)
		check_door(keycode, scene);
	spells_keys(keycode, scene);
}

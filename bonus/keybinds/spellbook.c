/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spellbook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 08:15:00 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/15 08:17:38 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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

void	evocation_spells(mlx_key_data_t keycode, t_scene *scene)
{
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

void	healing_spells(mlx_key_data_t keycode, t_scene *scene)
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
}

void	spells_keys(mlx_key_data_t keycode, t_scene *scene)
{
	healing_spells(keycode, scene);
	evocation_spells(keycode, scene);
	light_spell(keycode, scene);
}

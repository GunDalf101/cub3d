/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:37:36 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/15 08:15:12 by mbennani         ###   ########.fr       */
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

	scene = scene2;
	mlx_set_cursor_mode(scene->mlx_ptr, MLX_MOUSE_DISABLED);
	scene->key_data = keycode;
	if (keycode.key == MLX_KEY_LEFT_ALT)
		return (mlx_set_cursor_mode(scene->mlx_ptr, MLX_MOUSE_NORMAL));
	if (keycode.key == MLX_KEY_ESCAPE)
	{
		system("pkill afplay &");
		return (final_free(scene), exit(0));
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
	check_door(keycode, scene);
	spells_keys(keycode, scene);
}

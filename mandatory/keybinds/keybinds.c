/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:37:36 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/13 05:35:15 by mbennani         ###   ########.fr       */
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
		final_free(scene);
		exit(0);
	}
	player_movement(keycode, scene);
	player_rotation(keycode, scene);
}

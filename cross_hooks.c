/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhach <hbouhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:24:50 by mbennani          #+#    #+#             */
/*   Updated: 2023/10/27 22:11:53 by hbouhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

t_projectile *create_projectile(t_scene *scene, int projectile_type)
{
	t_projectile	*projectile;

	projectile = malloc(sizeof(t_projectile));
	projectile->pos[X] = scene->player->pos[X];
	projectile->pos[Y] = scene->player->pos[Y];
	projectile->dir[X] = scene->player->dir[X];
	projectile->dir[Y] = scene->player->dir[Y];
	projectile->speed = 0.6;
	projectile->damage = 20;
	projectile->v_move = 500;
	projectile->proj_type = projectile_type;
	if (projectile->proj_type == FIREBALL)
		projectile->proj_img = scene->fireball_img;
	else if (projectile->proj_type == ICEBALL)
		projectile->proj_img = scene->iceball_img;
	projectile->next = NULL;
	return (projectile);
}

void add_projectile(t_scene *scene, int projectile_type)
{
	t_projectile	*last_projectile;

	last_projectile = scene->projectiles;
	if (!last_projectile)
		scene->projectiles = create_projectile(scene, projectile_type);
	else
	{
		while (last_projectile->next)
			last_projectile = last_projectile->next;
		last_projectile->next = create_projectile(scene, projectile_type);
	}
}

void	hooker(mlx_key_data_t keycode, void *scene2)
{
	t_scene	*scene;
	scene = (t_scene *)scene2;
	scene->key_data = keycode;
	if (keycode.key == MLX_KEY_ESCAPE)
		exit(0);
	if (keycode.key == MLX_KEY_W && keycode.action == MLX_PRESS && scene->player->is_ded == FALSE)
		scene->player->forward = TRUE;
	else if (keycode.key == MLX_KEY_W && keycode.action == MLX_RELEASE)
		scene->player->forward = FALSE;
	if (keycode.key == MLX_KEY_S && keycode.action == MLX_PRESS && scene->player->is_ded == FALSE)
		scene->player->backwards = TRUE;
	else if (keycode.key == MLX_KEY_S && keycode.action == MLX_RELEASE)
		scene->player->backwards = FALSE;
	if (keycode.key == MLX_KEY_A && keycode.action == MLX_PRESS && scene->player->is_ded == FALSE)
		scene->player->left = TRUE;
	else if (keycode.key == MLX_KEY_A && keycode.action == MLX_RELEASE)
		scene->player->left = FALSE;
	if (keycode.key == MLX_KEY_D && keycode.action == MLX_PRESS && scene->player->is_ded == FALSE)
		scene->player->right = TRUE;
	else if (keycode.key == MLX_KEY_D && keycode.action == MLX_RELEASE)
		scene->player->right = FALSE;
	if (keycode.key == MLX_KEY_LEFT_SHIFT && keycode.action == MLX_PRESS && scene->player->is_ded == FALSE && scene->player->is_crouching == FALSE)
		scene->player->is_running = 3;
	else if (keycode.key == MLX_KEY_LEFT_SHIFT && keycode.action == MLX_RELEASE)
		scene->player->is_running = 1.5;
	if (keycode.key == MLX_KEY_LEFT_CONTROL && keycode.action == MLX_PRESS && scene->player->is_ded == FALSE)
	{
		scene->player->is_crouching = 50;
		scene->player->is_running = 0.75;
	}
	else if (keycode.key == MLX_KEY_LEFT_CONTROL && keycode.action == MLX_RELEASE && scene->player->is_ded == FALSE)
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
		system("afplay assets/Heal.mp3 &");
		scene->player->mana_points -= 20;
		if (scene->player->health_points + 20 > 100)
			scene->player->health_points = 100;
		else
			scene->player->health_points += 20;
	}
	if (keycode.key == MLX_KEY_1 && keycode.action == MLX_RELEASE && scene->player->is_ded == FALSE)
	{
		if (scene->player->mana_points >= 5)
		{
			system("afplay assets/FireBall.mp3 &");
			scene->player->mana_points -= 5;
			add_projectile(scene, FIREBALL);
		}
	}
	if (keycode.key == MLX_KEY_2 && keycode.action == MLX_RELEASE && scene->player->is_ded == FALSE)
	{
		if (scene->player->mana_points >= 5)
		{
			system("afplay assets/IceOrb.mp3 &");
			scene->player->mana_points -= 5;
			add_projectile(scene, ICEBALL);
		}
	}
}

void	hookercur(double xpos, double ypos, void* scene2)
{
	t_scene	*scene;
	static double	old_ypos;

	scene = (t_scene *)scene2;
	if (old_ypos == 0)
		old_ypos = ypos;
	if (!scene->player->is_ded)
		scene->player->p_angle = xpos / 80;
	if (old_ypos < ypos && !scene->player->is_ded)
		scene->player->central_angle -= 30.0;
	else if (old_ypos > ypos && !scene->player->is_ded)
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

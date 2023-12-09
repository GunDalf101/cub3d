/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_logic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:21:51 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/09 10:48:43 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	delete_projectile(t_scene *scene, t_projectile *projectile)
{
	t_projectile	*tmp;

	tmp = scene->projectiles;
	if (tmp == projectile)
	{
		scene->projectiles = tmp->next;
		free(tmp);
		tmp = NULL;
		return ;
	}
	while (tmp->next != projectile)
		tmp = tmp->next;
	tmp->next = tmp->next->next;
	free(projectile);
}

void	projectile_logic(t_scene *scene)
{
	t_projectile	*tmp;

	tmp = scene->projectiles;
	while (tmp)
	{
		if (tmp && projectile_collide(scene, tmp))
			delete_projectile(scene, tmp);
		tmp->pos[X] += tmp->dir[X] * tmp->speed;
		tmp->pos[Y] += tmp->dir[Y] * tmp->speed;
		tmp->proj_distance = sqrt(pow((tmp->pos[X] - scene->player->pos[X]), 2)
				+ pow((tmp->pos[Y] - scene->player->pos[Y]), 2));
		tmp = tmp->next;
	}
	scene->projectiles = proj_sort(scene->projectiles);
}

t_projectile	*create_projectile(t_scene *scene, int projectile_type)
{
	t_projectile	*projectile;

	projectile = malloc(sizeof(t_projectile));
	if (!projectile)
		return (final_free(scene), exit(1), NULL);
	projectile->pos[X] = scene->player->pos[X];
	projectile->pos[Y] = scene->player->pos[Y];
	projectile->dir[X] = scene->player->dir[X];
	projectile->dir[Y] = scene->player->dir[Y];
	projectile->speed = 0.8;
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

void	add_projectile(t_scene *scene, int projectile_type)
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

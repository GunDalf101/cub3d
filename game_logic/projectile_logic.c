/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_logic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:21:51 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/05 14:39:52 by mbennani         ###   ########.fr       */
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
		tmp = NULL;
		free(tmp);
		return ;
	}
	while (tmp->next != projectile)
		tmp = tmp->next;
	tmp->next = tmp->next->next;
	free(projectile);
}

t_projectile	*merge(t_projectile *left, t_projectile *right)
{
	t_projectile	dummy;
	t_projectile	*tail;

	tail = &dummy;
	while (left && right)
	{
		if (left->proj_distance > right->proj_distance)
		{
			tail->next = left;
			left = left->next;
		}
		else
		{
			tail->next = right;
			right = right->next;
		}
		tail = tail->next;
	}
	if (left)
		tail->next = left;
	else
		tail->next = right;
	return (dummy.next);
}

t_projectile	*proj_sort(t_projectile *head)
{
	t_projectile	*slow;
	t_projectile	*fast;
	t_projectile	*right;
	t_projectile	*left_sorted;
	t_projectile	*right_sorted;

	if (head == NULL || head->next == NULL)
		return (head);
	slow = head;
	fast = head->next;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	right = slow->next;
	slow->next = NULL;
	left_sorted = proj_sort(head);
	right_sorted = proj_sort(right);
	return (merge(left_sorted, right_sorted));
}

void	projectile_logic(t_scene *scene)
{
	t_projectile	*tmp;

	tmp = scene->projectiles;
	while (tmp)
	{
		if (tmp && (scene->map->map[(int)(tmp->pos[X])
				/ UNIT][(int)(tmp->pos[Y]) / UNIT] == '1'
				|| scene->map->map[(int)(tmp->pos[X]) / UNIT][(int)(tmp->pos[Y])
				/ UNIT] == 'P'))
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

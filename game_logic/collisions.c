/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:22:51 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/05 12:35:30 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

double	calculate_distance(int x1, int y1, int x2, int y2)
{
	return (sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)));
}

int	check_sprite_collision(int x, int y, t_scene scene, int indexer)
{
	double	distance;

	distance = calculate_distance(x, y, scene.sprites[indexer]->pos[X],
			scene.sprites[indexer]->pos[Y]);
	if (distance < scene.sprites[indexer]->collision_box)
		return (TRUE);
	return (FALSE);
}

void	dda_step(t_dda *dda, int *x, int *y)
{
	dda->err2 = 2 * dda->err;
	if (dda->err2 > -dda->dy)
	{
		dda->err -= dda->dy;
		(*x) += dda->sx;
	}
	if (dda->err2 < dda->dx)
	{
		dda->err += dda->dx;
		(*y) += dda->sy;
	}
}

int	collision_ray(t_dda dda, int x2, int y2, t_scene scene)
{
	dda.dx = abs(x2 - dda.x1);
	dda.dy = abs(y2 - dda.y1);
	if (dda.x1 < x2)
		dda.sx = 1;
	else
		dda.sx = -1;
	if (dda.y1 < y2)
		dda.sy = 1;
	else
		dda.sy = -1;
	dda.err = dda.dx - dda.dy;
	while (1)
	{
		if (check_sprite_collision(dda.x1, dda.y1, scene, scene.indexer))
			return (TRUE);
		if (dda.x1 == x2 && dda.y1 == y2)
			break ;
		dda_step(&dda, &dda.x1, &dda.y1);
	}
	return (FALSE);
}

int	collision_along_direction(t_scene *scene, int cas)
{
	t_dda	dda;

	dda.x1 = scene->player->pos[X];
	dda.y1 = scene->player->pos[Y];
	if (cas == 1)
		return (collision_ray(dda, scene->player->pos[X], scene->player->pos[Y]
				+ scene->player->dir[Y] * scene->move_speed, *scene));
	else if (cas == 2)
		return (collision_ray(dda, scene->player->pos[X] + scene->player->dir[X]
				* scene->move_speed, scene->player->pos[Y], *scene));
	else if (cas == 3)
		return (collision_ray(dda, scene->player->pos[X], scene->player->pos[Y]
				- scene->player->dir[Y] * scene->move_speed, *scene));
	else if (cas == 4)
		return (collision_ray(dda, scene->player->pos[X] - scene->player->dir[X]
				* scene->move_speed, scene->player->pos[Y], *scene));
	return (FALSE);
}

int	collision_along_plane(t_scene *scene, int cas)
{
	t_dda	dda;

	dda.x1 = scene->player->pos[X];
	dda.y1 = scene->player->pos[Y];
	if (cas == 5)
		return (collision_ray(dda, scene->player->pos[X], scene->player->pos[Y]
				- scene->player->plane[Y] * scene->move_speed, *scene));
	else if (cas == 6)
		return (collision_ray(dda, scene->player->pos[X]
				- scene->player->plane[X] * scene->move_speed,
				scene->player->pos[Y], *scene));
	else if (cas == 7)
		return (collision_ray(dda, scene->player->pos[X], scene->player->pos[Y]
				+ scene->player->plane[Y] * scene->move_speed, *scene));
	else if (cas == 8)
		return (collision_ray(dda, scene->player->pos[X]
				+ scene->player->plane[X] * scene->move_speed,
				scene->player->pos[Y], *scene));
	return (FALSE);
}

int	does_it_collide(t_scene *scene, int cas)
{
	int	i;

	i = 0;
	while (i < scene->sprite_count)
	{
		scene->indexer = i;
		if (collision_along_direction(scene, cas))
			return (TRUE);
		if (collision_along_direction(scene, cas))
			return (TRUE);
		if (collision_along_direction(scene, cas))
			return (TRUE);
		if (collision_along_direction(scene, cas))
			return (TRUE);
		if (collision_along_plane(scene, cas))
			return (TRUE);
		if (collision_along_plane(scene, cas))
			return (TRUE);
		if (collision_along_plane(scene, cas))
			return (TRUE);
		if (collision_along_plane(scene, cas))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

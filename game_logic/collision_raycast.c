/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_raycast.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:08:54 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/09 15:41:15 by mbennani         ###   ########.fr       */
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
	if (indexer < scene.sprite_count
		&& distance < scene.sprites[indexer]->collision_box)
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

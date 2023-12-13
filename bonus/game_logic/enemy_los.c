/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_los.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:51:37 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/12 19:37:06 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

double	check_distance(int x1, int y1, int x2, int y2)
{
	return (sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)));
}

int	check_wall_collision(int x, int y, t_scene scene, int war_index)
{
	double	distance;

	distance = scene.sprites[war_index]->sprite_distance;
	if (scene.map->map[x / UNIT][y / UNIT] == '1' || scene.map->map[x / UNIT][y
		/ UNIT] == 'D' || distance < 25)
		return (TRUE);
	return (FALSE);
}

void	vision_step(t_dda *dda, int *x, int *y)
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

int	line_o_sight(t_dda dda, int x2, int y2, t_scene scene)
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
		if (check_wall_collision(dda.x1, dda.y1, scene, scene.war_index))
			return (FALSE);
		if (dda.x1 == x2 && dda.y1 == y2)
			break ;
		vision_step(&dda, &dda.x1, &dda.y1);
	}
	return (TRUE);
}

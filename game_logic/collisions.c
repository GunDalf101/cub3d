/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:22:51 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/09 11:31:46 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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

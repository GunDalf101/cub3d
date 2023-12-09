/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_sprite_interaction.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 10:48:27 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/09 10:58:22 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	projectile_hit(t_projectile *projectile, t_sprite *sprite)
{
	int	k;
	int	l;
	int	hitbox;

	k = sprite->pos[X];
	l = sprite->pos[Y];
	hitbox = sprite->hitbox;
	if (projectile->pos[X] < k + hitbox && projectile->pos[X] > k - hitbox
		&& projectile->pos[Y] < l + hitbox && projectile->pos[Y] > l - hitbox)
	{
		sprite->hitpoint -= projectile->damage;
		if (sprite->hitpoint <= 0)
		{
			sprite->pos[X] = -UNIT;
			sprite->pos[Y] = -UNIT;
		}
		return (1);
	}
	return (0);
}

int	projectile_collide(t_scene *scene, t_projectile *projectile)
{
	int	i;
	int	j;
	int	it;

	it = 0;
	i = projectile->pos[X];
	j = projectile->pos[Y];
	while (it < scene->sprite_count)
	{
		if (projectile_hit(projectile, scene->sprites[it]))
			return (1);
		it++;
	}
	return (0);
}

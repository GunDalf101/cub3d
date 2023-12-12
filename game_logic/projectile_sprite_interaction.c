/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_sprite_interaction.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 10:48:27 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/13 00:28:57 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	calcul_score(t_sprite *sprite, t_scene *scene)
{
	if (sprite->sprite_type == WARLOCK)
	{
		scene->player->mana_points += 10;
		scene->score += 50;
	}
	else if (sprite->sprite_type == BARREL)
		scene->score += 50;
	else if (sprite->sprite_type == PILLAR)
		scene->score += 10;
	else if (sprite->sprite_type == MANAORB)
		scene->score += 0;
}

int	projectile_hit(t_projectile *projectile, t_sprite *sprite, t_scene *scene)
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
			calcul_score(sprite, scene);
			printf("score: %d\n", scene->score);
			sprite->pos[X] = -UNIT;
			sprite->pos[Y] = -UNIT;
			system("afplay assets/ghostdeath.mp3 &");
			sprite->state = DEAD;
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
		if (projectile_hit(projectile, scene->sprites[it], scene))
			return (1);
		it++;
	}
	return (0);
}

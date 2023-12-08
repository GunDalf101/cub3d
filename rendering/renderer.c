/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:16:36 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/08 01:38:08 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	sprites_only(t_scene scene)
{
	int	i;

	i = 0;
	while (i < scene.sprite_count)
	{
		if (scene.sprites[i]->animation_img)
			animated_sprite(scene, i);
		else
			spawn_sprites(&scene, i);
		i++;
	}
}

void	sprites_projectiles(t_scene scene)
{
	int				i;
	t_projectile	*tmp;

	i = 0;
	while (i < scene.sprite_count)
	{
		scene.sprites[i]->sprite_distance = sqrt(pow(scene.sprites[i]->pos[Y]
					- scene.player->pos[Y], 2) + pow(scene.sprites[i]->pos[X]
					- scene.player->pos[X], 2));
		i++;
	}
	sort_sprites(scene.sprites, scene.sprite_count);
	sprites_only(scene);
	tmp = scene.projectiles;
	while (tmp)
	{
		spawn_proj(&scene, tmp);
		tmp = tmp->next;
	}
}

void	renderitall(t_scene scene)
{
	sky_floor_render(scene);
	ray_caster(&scene);
	sprites_projectiles(scene);
	draw_minimap_circle(&scene);
	drawbar(scene);
	if (scene.player->is_ded == TRUE)
		death_screen(scene);
	mlx_image_to_window(scene.mlx_ptr, scene.mlx_img, 0, 0);
	occasional_free(&scene);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:16:36 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/06 17:40:23 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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
	i = 0;
	while (i < scene.sprite_count)
	{
		spawn_sprites(&scene, i);
		i++;
	}
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
}

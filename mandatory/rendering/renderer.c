/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:16:36 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/16 08:13:21 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	heavens_and_earth(t_scene scene)
{
	t_dda	dda;
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (++i < scene.player->central_angle + WIN_HEIGHT / 2
		- scene.player->crouch)
	{
		dda.x1 = 0;
		dda.y1 = i;
		dda.color = scene.map->ceiling_rgb[0] << 24 | scene.map->\
		ceiling_rgb[1] << 16 | scene.map->ceiling_rgb[2] << 8 | 255;
		drawline(&dda, WIN_WIDTH, i, scene);
	}
	i = scene.player->central_angle + WIN_HEIGHT / 2 - scene.player->crouch;
	while (++i < WIN_HEIGHT)
	{
		dda.x1 = 0;
		dda.y1 = i;
		dda.color = scene.map->floor_rgb[0] << 24 | scene.map->\
		floor_rgb[1] << 16 | scene.map->floor_rgb[2] << 8 | 255;
		drawline(&dda, WIN_WIDTH, i, scene);
	}
}

void	renderitall(t_scene scene)
{
	heavens_and_earth(scene);
	ray_caster(&scene);
	mlx_image_to_window(scene.mlx_ptr, scene.mlx_img, 0, 0);
	occasional_free(&scene);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_loader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:03:15 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/07 13:59:07 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	load_sprites(t_scene *scene)
{
	scene->barrel_tex = mlx_load_png("assets/barrel_01.png");
	if (!scene->barrel_tex)
		exit(0);
	scene->barrel_img = mlx_texture_to_image(scene->mlx_ptr, scene->barrel_tex);
	mlx_resize_image(scene->barrel_img, 415 * WIN_HEIGHT / 1200, 250
		* WIN_HEIGHT / 1200);
	mlx_delete_texture(scene->barrel_tex);
	scene->pillar_tex = mlx_load_png("assets/Pillar.png");
	if (!scene->pillar_tex)
		exit(0);
	scene->pillar_img = mlx_texture_to_image(scene->mlx_ptr, scene->pillar_tex);
	mlx_resize_image(scene->pillar_img, 500 * WIN_HEIGHT / 1200, 500
		* WIN_HEIGHT / 1200);
	mlx_delete_texture(scene->pillar_tex);
	scene->manaorb_tex = mlx_load_png("assets/ManaOrb.png");
	if (!scene->manaorb_tex)
		exit(0);
	scene->manaorb_img = mlx_texture_to_image(scene->mlx_ptr,
			scene->manaorb_tex);
	mlx_resize_image(scene->manaorb_img, 251 * WIN_HEIGHT / 1200, 282
		* WIN_HEIGHT / 1200);
	mlx_delete_texture(scene->manaorb_tex);
}

void	load_floor_textures(t_scene *scene)
{
	scene->floor_tex = mlx_load_png("textures/floor.png");
	if (!scene->floor_tex)
		exit(0);
	scene->floor_img = mlx_texture_to_image(scene->mlx_ptr, scene->floor_tex);
	mlx_resize_image(scene->floor_img, WIN_WIDTH, WIN_HEIGHT);
	mlx_delete_texture(scene->floor_tex);
	scene->ceil_tex = mlx_load_png("textures/ceil.png");
	if (!scene->ceil_tex)
		exit(0);
	scene->ceil_img = mlx_texture_to_image(scene->mlx_ptr, scene->ceil_tex);
	mlx_resize_image(scene->ceil_img, WIN_WIDTH, WIN_HEIGHT);
	mlx_delete_texture(scene->ceil_tex);
	scene->trap_tex = mlx_load_png("textures/lava.png");
	if (!scene->trap_tex)
		exit(0);
	scene->trap_img = mlx_texture_to_image(scene->mlx_ptr,
			scene->trap_tex);
	mlx_resize_image(scene->trap_img, WIN_WIDTH, WIN_WIDTH);
	mlx_delete_texture(scene->trap_tex);
	printf("trap loaded\n");
}

void	load_projectiles(t_scene *scene)
{
	scene->fireball_tex = mlx_load_png("assets/FireBall.png");
	if (!scene->fireball_tex)
		exit(0);
	scene->fireball_img = mlx_texture_to_image(scene->mlx_ptr,
			scene->fireball_tex);
	mlx_resize_image(scene->fireball_img, 200 * WIN_HEIGHT / 1200, 200
		* WIN_HEIGHT / 1200);
	mlx_delete_texture(scene->fireball_tex);
	scene->iceball_tex = mlx_load_png("assets/IceBall.png");
	if (!scene->iceball_tex)
		exit(0);
	scene->iceball_img = mlx_texture_to_image(scene->mlx_ptr,
			scene->iceball_tex);
	mlx_resize_image(scene->iceball_img, 150 * WIN_HEIGHT / 1200, 150
		* WIN_HEIGHT / 1200);
	mlx_delete_texture(scene->iceball_tex);
}

void	sprite_count(t_scene *scene)
{
	int	i;
	int	count;
	int	j;

	i = 0;
	count = 0;
	while (i < scene->map->map_height)
	{
		j = 0;
		while (j < scene->map->map_width)
		{
			if (scene->map->map[i][j] == 'B')
				count++;
			if (scene->map->map[i][j] == 'P')
				count++;
			if (scene->map->map[i][j] == 'M')
				count++;
			j++;
		}
		i++;
	}
	scene->sprite_count = count;
}

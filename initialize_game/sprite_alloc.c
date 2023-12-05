/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 22:04:52 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/05 11:20:33 by mbennani         ###   ########.fr       */
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

void	allocat_barrel(t_scene *scene, int i, int j, int *count)
{
	scene->sprites[*count] = ft_calloc(1, sizeof(t_sprite));
	if (!scene->sprites[*count])
		exit(0);
	scene->sprites[*count]->sprite_img = scene->barrel_img;
	scene->sprites[*count]->v_move = 1100 * WIN_HEIGHT / 1200;
	scene->sprites[*count]->collision_box = 40;
	scene->sprites[*count]->pos[Y] = j * UNIT + UNIT / 2;
	scene->sprites[*count]->pos[X] = i * UNIT + UNIT / 2;
	(*count)++;
}

void	allocat_pillar(t_scene *scene, int i, int j, int *count)
{
	scene->sprites[*count] = ft_calloc(1, sizeof(t_sprite));
	if (!scene->sprites[*count])
		exit(0);
	scene->sprites[*count]->sprite_img = scene->pillar_img;
	scene->sprites[*count]->v_move = 50 * WIN_HEIGHT / 1200;
	scene->sprites[*count]->collision_box = 40;
	scene->sprites[*count]->pos[Y] = j * UNIT + UNIT / 2;
	scene->sprites[*count]->pos[X] = i * UNIT + UNIT / 2;
	(*count)++;
}

void	allocat_manaorb(t_scene *scene, int i, int j, int *count)
{
	scene->sprites[*count] = ft_calloc(1, sizeof(t_sprite));
	if (!scene->sprites[*count])
		exit(0);
	scene->sprites[*count]->sprite_img = scene->manaorb_img;
	scene->sprites[*count]->v_move = -500 * WIN_HEIGHT / 1200;
	scene->sprites[*count]->collision_box = 0;
	scene->sprites[*count]->pos[Y] = j * UNIT + UNIT / 2;
	scene->sprites[*count]->pos[X] = i * UNIT + UNIT / 2;
	(*count)++;
}

void	allocat_sprites(t_scene *scene)
{
	int	i;
	int	count;
	int	j;

	scene->sprites = ft_calloc(scene->sprite_count, sizeof(t_sprite *));
	if (!scene->sprites)
		exit(0);
	i = 0;
	count = 0;
	while (i < scene->map->map_height)
	{
		j = 0;
		while (j < scene->map->map_width)
		{
			if (scene->map->map[i][j] == 'B')
				allocat_barrel(scene, i, j, &count);
			if (scene->map->map[i][j] == 'P')
				allocat_pillar(scene, i, j, &count);
			if (scene->map->map[i][j] == 'M')
				allocat_manaorb(scene, i, j, &count);
			j++;
		}
		i++;
	}
}

void	initsprites(t_scene *scene)
{
	load_sprites(scene);
	load_projectiles(scene);
	sprite_count(scene);
	allocat_sprites(scene);
}

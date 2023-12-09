/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_loader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:03:15 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/09 12:47:01 by mbennani         ###   ########.fr       */
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
	scene->trap_img = mlx_texture_to_image(scene->mlx_ptr, scene->trap_tex);
	mlx_resize_image(scene->trap_img, WIN_WIDTH, WIN_WIDTH);
	mlx_delete_texture(scene->trap_tex);
	scene->door_tex = mlx_load_png("textures/door.png");
	if (!scene->door_tex)
		exit(0);
	scene->door_img = mlx_texture_to_image(scene->mlx_ptr, scene->door_tex);
	mlx_resize_image(scene->door_img, WIN_WIDTH, WIN_WIDTH);
	mlx_delete_texture(scene->door_tex);
	// printf("trap loaded\n");
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

void	load_warlock(void *mlxptr, t_scene *scene)
{
	int				i;
	mlx_texture_t	*texture;
	char			warlock_path[29];

	ft_strlcpy(warlock_path, "assets/evil_wiz/evilwiz0.png", 29);
	scene->evil_warlock = malloc(sizeof(mlx_image_t *) * 10);
	if (!scene->evil_warlock)
		exit(1);
	i = 0;
	while (i < 10)
	{
		texture = mlx_load_png(warlock_path);
		if (!texture)
			exit(1);
		scene->evil_warlock[i] = mlx_texture_to_image(mlxptr, texture);
		if (!scene->evil_warlock[i])
			exit(1);
		mlx_resize_image(scene->evil_warlock[i], 500 * WIN_HEIGHT / 1200, 500
			* WIN_HEIGHT / 1200);
		mlx_delete_texture(texture);
		warlock_path[23] += 1;
		i++;
	}
}

void	sprite_count(t_scene *scene)
{
	int	i;
	int	count;
	int	j;

	i = 0;
	count = 0;
	scene->anim_count = 0;
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
			if (scene->map->map[i][j] == 'V')
				count++;
			j++;
		}
		i++;
	}
	scene->sprite_count = count;
}

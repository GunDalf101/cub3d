/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:12:11 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/15 13:28:41 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	allocate_sprite_memory(t_scene *scene)
{
	scene->sprites = ft_calloc(scene->sprite_count, sizeof(t_sprite *));
	if (!scene->sprites)
		exit(0);
}

void	create_and_initialize_sprites(t_scene *scene)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (++i < scene->map->map_height)
	{
		j = -1;
		while (++j < scene->map->map_width)
		{
			if (scene->map->map[i][j] == 'B')
				allocat_barrel(scene, i, j, &count);
			else if (scene->map->map[i][j] == 'P')
				allocat_pillar(scene, i, j, &count);
			else if (scene->map->map[i][j] == 'M')
				allocat_manaorb(scene, i, j, &count);
			else if (scene->map->map[i][j] == 'V')
				allocat_warlock(scene, i, j, &count);
			else if (scene->map->map[i][j] == 'Z'
				|| scene->map->map[i][j] == 'Y')
				allocat_portal(scene, i, j, &count);
		}
	}
}

void	allocat_sprites(t_scene *scene)
{
	allocate_sprite_memory(scene);
	create_and_initialize_sprites(scene);
}

mlx_texture_t	*load_single_sword_texture(void *mlxptr, const char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	(void)mlxptr;
	if (!texture)
	{
		fprintf(stderr, "Error loading texture at path: %s\n", path);
		exit(1);
	}
	return (texture);
}

void	load_sword(void *mlxptr, t_scene *scene)
{
	int		i;
	char	sword_path[30];

	ft_strlcpy(sword_path, "assets/sword/finnsword01.png", 30);
	scene->finn_sword = malloc(sizeof(mlx_image_t *) * 18);
	if (!scene->finn_sword)
		exit(1);
	i = 0;
	while (i < 18)
	{
		scene->finn_sword[i] = mlx_texture_to_image(mlxptr,
				load_single_sword_texture(mlxptr, sword_path));
		mlx_resize_image(scene->finn_sword[i], WIN_WIDTH, 360 * WIN_WIDTH / 640);
		if (i % 10 == 8)
		{
			sword_path[23] = '0';
			sword_path[22] += 1;
		}
		else
		{
			sword_path[23] += 1;
		}
		i++;
	}
}

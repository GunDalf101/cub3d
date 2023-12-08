/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:43:00 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/08 01:11:17 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	occasional_free(t_scene *scene)
{
	int	i;

	i = 0;
	if (scene->z_buffer)
		free(scene->z_buffer);
	scene->z_buffer = NULL;
	while (i < WIN_WIDTH)
	{
		free(scene->player->vision_rays[i]);
		scene->player->vision_rays[i] = NULL;
		i++;
	}
	if (scene->player->vision_rays)
		free(scene->player->vision_rays);
	scene->player->vision_rays = NULL;
	return (1);
}

void	free_parsin_elements(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->map->map_height)
	{
		free(scene->map->map[i]);
		i++;
	}
	free(scene->map->map);
	i = 0;
	while (i < 4)
	{
		free(scene->map->textures_paths[i]);
		i++;
	}
	free(scene->map->textures_paths);
	free(scene->map->textures_mlx_imgs);
	i = 0;
	while (i < 10)
	{
		mlx_delete_image(scene->mlx_ptr, scene->evil_warlock[i]);
		i++;
	}
	free(scene->evil_warlock);
}

int	final_free(t_scene *scene)
{
	t_projectile	*tmp;
	int				i;

	i = 0;
	free_parsin_elements(scene);
	while (i < scene->sprite_count)
	{
		free(scene->sprites[i]);
		i++;
	}
	free(scene->sprites);
	tmp = scene->projectiles;
	while (tmp)
	{
		scene->projectiles = scene->projectiles->next;
		mlx_delete_image(scene->mlx_ptr, tmp->proj_img);
		free(tmp);
		tmp = scene->projectiles;
	}
	free(scene->map);
	free(scene->player);
	mlx_delete_image(scene->mlx_ptr, scene->mlx_img);
	return (1);
}

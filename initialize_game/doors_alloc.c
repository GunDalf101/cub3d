/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:40:53 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/11 19:20:44 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	load_end(t_scene *scene)
{
	scene->end_tex = mlx_load_png("textures/portal.png");
	if (!scene->end_tex)
		exit(0);
	scene->end_img = mlx_texture_to_image(scene->mlx_ptr, scene->end_tex);
	mlx_resize_image(scene->end_img, 500, 500);
	mlx_delete_texture(scene->end_tex);
	scene->win_tex = mlx_load_png("assets/victory.png");
	if (!scene->win_tex)
		exit(0);
	scene->win_img = mlx_texture_to_image(scene->mlx_ptr, scene->win_tex);
	mlx_resize_image(scene->win_img, WIN_WIDTH, scene->win_img->height
		* WIN_WIDTH / scene->win_img->width);
	mlx_delete_texture(scene->win_tex);
	scene->ending_tex = mlx_load_png("assets/ending.png");
	if (!scene->ending_tex)
		exit(0);
	scene->ending_img = mlx_texture_to_image(scene->mlx_ptr, scene->ending_tex);
	mlx_resize_image(scene->ending_img, WIN_WIDTH - 1, WIN_HEIGHT - 1);
	mlx_delete_texture(scene->ending_tex);
}

void	allocat_door(t_scene *scene, int i, int j, int *count)
{
	scene->doors[*count] = ft_calloc(1, sizeof(t_door));
	if (!scene->doors[*count])
		exit(0);
	scene->doors[*count]->pos[Y] = j;
	scene->doors[*count]->pos[X] = i;
	scene->doors[*count]->state = CLOSED;
	(*count)++;
}

void	set_pole_coordinates(t_scene *scene, int i, int j)
{
	if (scene->map->map[i][j] == 'Z')
	{
		scene->north_pole[X] = i;
		scene->north_pole[Y] = j;
	}
	if (scene->map->map[i][j] == 'Y')
	{
		scene->south_pole[X] = i;
		scene->south_pole[Y] = j;
	}
}

void	allocat_doors(t_scene *scene)
{
	int	i;
	int	count;
	int	j;

	scene->doors = ft_calloc(scene->door_count, sizeof(t_door *));
	if (!scene->doors)
		exit(0);
	i = -1;
	count = 0;
	while (++i < scene->map->map_height)
	{
		j = -1;
		while (++j < scene->map->map_width)
		{
			if (scene->map->map[i][j] == 'D')
				allocat_door(scene, i, j, &count);
			set_pole_coordinates(scene, i, j);
		}
	}
}

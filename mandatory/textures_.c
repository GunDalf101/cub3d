/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 03:34:36 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/15 12:09:20 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	perror_faulty_texuture(char *fpath)
{
	printf("could not load texture: [%s]\n", fpath);
	exit(1);
}

int	load_textures(void *mlxptr, t_map *map)
{
	int				i;
	mlx_texture_t	*texture;

	map->textures_mlx_imgs = malloc(sizeof(mlx_image_t *) * 4);
	if (!map->textures_mlx_imgs)
		return (1);
	i = 0;
	while (i < 4)
	{
		texture = mlx_load_png(map->textures_paths[i]);
		if (!texture)
			perror_faulty_texuture(map->textures_paths[i]);
		map->textures_mlx_imgs[i] = mlx_texture_to_image(mlxptr, texture);
		if (!map->textures_mlx_imgs[i])
			perror_faulty_texuture(map->textures_paths[i]);
		mlx_resize_image(map->textures_mlx_imgs[i], UNIT, UNIT);
		mlx_delete_texture(texture);
		i++;
	}
	return (0);
}

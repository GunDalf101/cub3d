/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 00:46:52 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/07 14:06:25 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdio.h>

void	mlx_exit()
{
	system("leaks cub3d");
}

int	main(int argc, char *argv[])
{
	atexit(mlx_exit);
	t_scene		scene;
	scene.map = ft_calloc(sizeof(t_map), 1);
	if (argc != 2)
		return (1);
	if (parser(argv[1], scene.map))
	{
		printf("ERROR\n");
		return (1);
	}

	printf("ceiling: %d,%d,%d\n", scene.map->ceiling_rgb[0], scene.map->ceiling_rgb[1], scene.map->ceiling_rgb[2]);
	printf("floor: %d,%d,%d\n", scene.map->floor_rgb[0], scene.map->floor_rgb[1], scene.map->floor_rgb[2]);

	for (int i = 0; scene.map->map[i]; i++)
	{
		printf(">> [%s] <<\n", scene.map->map[i]);
	}

	printf("map props: %d,%d\n", scene.map->map_width, scene.map->map_height);
	scene.projectiles = NULL;
	allocat_player(&scene);
	scene.mlx_ptr = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Escape From GunDalf", 1);
	if (load_textures(scene.mlx_ptr, scene.map))
		return (1);
	initsprites(&scene);
	scene.time = 0;
	scene.mlx_img = mlx_new_image(scene.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx_loop_hook(scene.mlx_ptr, gameloop, &scene);
	mlx_set_cursor_mode(scene.mlx_ptr, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(scene.mlx_ptr, hookercur, &scene);
	mlx_key_hook(scene.mlx_ptr, hooker, &scene);
	mlx_loop(scene.mlx_ptr);
	return (0);
}

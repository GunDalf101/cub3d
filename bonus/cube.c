/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 00:46:52 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/15 05:09:56 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdio.h>

void	hookermouse(mouse_key_t button, action_t action, \
modifier_key_t mods, void *scene2)
{
	t_scene	*scene;

	scene = (t_scene *)scene2;
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS && \
	!scene->win && !scene->player->is_ded && !scene->player->attacking)
		melee_attack(scene);
}

int	main(int argc, char *argv[])
{
	t_scene	scene;

	if (srand(time(NULL)), argc != 2)
		return (1);
	if (WIN_HEIGHT < 500 || WIN_WIDTH < 500)
		return (1);
	scene.map = ft_calloc(sizeof(t_map), 1);
	if (!scene.map)
		return (1);
	if (parser(argv[1], scene.map))
		return (printf("ERROR\n"), 1);
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
	mlx_mouse_hook(scene.mlx_ptr, hookermouse, &scene);
	mlx_key_hook(scene.mlx_ptr, hooker, &scene);
	mlx_loop(scene.mlx_ptr);
	return (0);
}

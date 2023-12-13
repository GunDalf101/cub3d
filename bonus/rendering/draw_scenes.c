/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scenes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:39:38 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/13 04:31:30 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	draw_ending(t_scene scene)
{
	t_death	death;

	death.i = 0;
	while (death.i++ < scene.ending_img->height - 1)
	{
		death.j = 0;
		while (death.j++ < scene.ending_img->width - 1)
		{
			death.r = scene.ending_img->pixels[death.i * 4
				* scene.ending_img->width + death.j * 4];
			death.g = scene.ending_img->pixels[death.i * 4
				* scene.ending_img->width + death.j * 4 + 1];
			death.b = scene.ending_img->pixels[death.i * 4
				* scene.ending_img->width + death.j * 4 + 2];
			death.a = scene.ending_img->pixels[death.i * 4
				* scene.ending_img->width + death.j * 4 + 3];
			if (death.a == 0)
				continue ;
			mlx_put_pixel(scene.mlx_img, death.j, death.i, ft_pixel(death.r,
					death.g, death.b, death.a));
		}
	}
}

void	display_sword(t_scene *scene, int frame, t_death death)
{
	while (death.i++ < scene->finn_sword[frame / 1]->height - 1)
	{
		death.j = 0;
		while (death.j++ < scene->finn_sword[frame / 1]->width - 1)
		{
			death.r = scene->finn_sword[frame / 1]->pixels[death.i * 4
				* scene->finn_sword[frame / 1]->width + death.j * 4];
			death.g = scene->finn_sword[frame / 1]->pixels[death.i * 4
				* scene->finn_sword[frame / 1]->width + death.j * 4 + 1];
			death.b = scene->finn_sword[frame / 1]->pixels[death.i * 4
				* scene->finn_sword[frame / 1]->width + death.j * 4 + 2];
			death.a = scene->finn_sword[frame / 1]->pixels[death.i * 4
				* scene->finn_sword[frame / 1]->width + death.j * 4 + 3];
			if (death.a == 0 || (death.r <= 1 && death.g <= 1 && death.b <= 1))
				continue ;
			mlx_put_pixel(scene->mlx_img, death.j + WIN_WIDTH / 2
				- scene->finn_sword[frame / 1]->width / 2, death.i + WIN_HEIGHT
				- scene->finn_sword[frame / 1]->height, ft_pixel(death.r,
					death.g, death.b, death.a));
		}
	}
}

void	draw_attack(t_scene *scene)
{
	t_death		death;
	static int	frame;

	death.i = 0;
	if (frame >= 18)
	{
		scene->player->attacking = FALSE;
		frame = 0;
		return ;
	}
	display_sword(scene, frame, death);
	if (scene->player->attacking == TRUE)
		frame++;
}

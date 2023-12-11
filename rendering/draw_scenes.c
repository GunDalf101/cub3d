/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scenes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:39:38 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/11 20:39:56 by mbennani         ###   ########.fr       */
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

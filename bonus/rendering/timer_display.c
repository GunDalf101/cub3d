/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 23:14:17 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/10 23:22:20 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	drawtimer(t_scene scene)
{
	t_death	death;

	if (!scene.timer.timer_img)
		return ;
	death.i = 0;
	while (death.i++ < scene.timer.timer_img->height)
	{
		death.j = 0;
		while (death.j++ < scene.timer.timer_img->width)
		{
			death.r = scene.timer.timer_img->pixels[death.i * 4
				* scene.timer.timer_img->width + death.j * 4];
			death.g = scene.timer.timer_img->pixels[death.i * 4
				* scene.timer.timer_img->width + death.j * 4 + 1];
			death.b = scene.timer.timer_img->pixels[death.i * 4
				* scene.timer.timer_img->width + death.j * 4 + 2];
			death.a = scene.timer.timer_img->pixels[death.i * 4
				* scene.timer.timer_img->width + death.j * 4 + 3];
			if (death.a == 0)
				continue ;
			mlx_put_pixel(scene.mlx_img, death.j + WIN_WIDTH - 160, death.i
				+ WIN_HEIGHT - 40, ft_pixel(death.r, death.g, death.b,
					death.a));
		}
	}
}

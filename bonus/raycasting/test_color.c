/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 04:35:55 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/14 05:13:44 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	test_color(t_scene *scene, t_floor_cast *floor)
{
	double		intensity;
	u_int8_t	r;
	u_int8_t	g;
	u_int8_t	b;
	u_int8_t	a;

	intensity = 1 / ((floor->current_dist * 0.3) + 1);
	r = (scene->floor_img->pixels[scene->floor_img->width * floor->ty * 4
			+ floor->tx * 4] / 2
			+ scene->trap_img->pixels[scene->trap_img->width * floor->ty * 4
			+ floor->tx * 4] / 2) * intensity;
	g = ((scene->floor_img->pixels[scene->floor_img->width * floor->ty * 4
				+ floor->tx * 4 + 1] / 2)
			+ scene->trap_img->pixels[scene->trap_img->width * floor->ty * 4
			+ floor->tx * 4 + 1] / 2) * intensity;
	b = ((scene->floor_img->pixels[scene->floor_img->width * floor->ty * 4
				+ floor->tx * 4 + 2] / 2)
			+ scene->trap_img->pixels[scene->trap_img->width * floor->ty * 4
			+ floor->tx * 4 + 2] / 2) * intensity;
	a = (scene->floor_img->pixels[scene->floor_img->width * floor->ty * 4
			+ floor->tx * 4 + 3] / 2)
		+ scene->trap_img->pixels[scene->trap_img->width * floor->ty * 4
		+ floor->tx * 4 + 3] / 2;
	return (ft_pixel(r, g, b, a));
}

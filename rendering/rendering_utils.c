/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:51:16 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/06 17:10:02 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int32_t	ft_pixel(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	update_error_and_position(t_dda *dda, int *x, int *y)
{
	dda->err2 = 2 * dda->err;
	if (dda->err2 > -dda->dy)
	{
		dda->err -= dda->dy;
		(*x) += dda->sx;
	}
	if (dda->err2 < dda->dx)
	{
		dda->err += dda->dx;
		(*y) += dda->sy;
	}
}

void	set_signs(t_dda *dda, int x2, int y2)
{
	if (dda->x1 < x2)
		dda->sx = 1;
	else
		dda->sx = -1;
	if (dda->y1 < y2)
		dda->sy = 1;
	else
		dda->sy = -1;
}

int	reached_endpoint(t_dda *dda, int x2, int y2)
{
	return (dda->x1 == x2 && dda->y1 == y2);
}

void	drawline(t_dda *dda, int x2, int y2, t_scene scene)
{
	dda->dx = abs(x2 - dda->x1);
	dda->dy = abs(y2 - dda->y1);
	set_signs(dda, x2, y2);
	dda->err = dda->dx - dda->dy;
	while (!reached_endpoint(dda, x2, y2))
	{
		mlx_put_pixel(scene.mlx_img, dda->x1, dda->y1, dda->color);
		update_error_and_position(dda, &(dda->x1), &(dda->y1));
	}
}

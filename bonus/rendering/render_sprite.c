/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:17:02 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/15 10:54:13 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	sprite_coloring(t_scene *scene, int count, int stripe, int j)
{
	double		intensity;
	u_int8_t	r;
	u_int8_t	g;
	u_int8_t	b;
	u_int8_t	a;

	intensity = 1 / (((scene->sprites[count]->sprite_distance / UNIT) \
	* scene->light_multiplier) + 1);
	r = scene->sprites[count]->sprite_img->pixels[scene->sprites[count]->tex[Y]
		* 4 * scene->sprites[count]->sprite_img->width
		+ scene->sprites[count]->tex[X] * 4] * intensity;
	g = scene->sprites[count]->sprite_img->pixels[scene->sprites[count]->tex[Y]
		* 4 * scene->sprites[count]->sprite_img->width
		+ scene->sprites[count]->tex[X] * 4 + 1] * intensity;
	b = scene->sprites[count]->sprite_img->pixels[scene->sprites[count]->tex[Y]
		* 4 * scene->sprites[count]->sprite_img->width
		+ scene->sprites[count]->tex[X] * 4 + 2] * intensity;
	a = scene->sprites[count]->sprite_img->pixels[scene->sprites[count]->tex[Y]
		* 4 * scene->sprites[count]->sprite_img->width
		+ scene->sprites[count]->tex[X] * 4 + 3];
	if (a < 100)
		return ;
	mlx_put_pixel(scene->mlx_img, stripe, scene->player->central_angle
		- scene->player->crouch + j, ft_pixel(r, g, b, a));
}

void	calculate_texture_coordinates(t_scene *scene, int count, int stripe)
{
	scene->sprites[count]->tex[X] = (int)(256 * (stripe
				- (-scene->sprites[count]->sprite_width / 2
					+ scene->sprites[count]->sprite_screen_x))
			* scene->sprites[count]->sprite_img->width
			/ scene->sprites[count]->sprite_width) / 256;
}

void	render_vertical_lines(t_scene *scene, int count, int stripe, int j)
{
	while (j < scene->sprites[count]->end[Y])
	{
		scene->sprites[count]->d = (j - scene->sprites[count]->v_move_screen)
			* 256 - WIN_HEIGHT * 128 + scene->sprites[count]->sprite_height
			* 128;
		scene->sprites[count]->tex[Y] = ((scene->sprites[count]->d
					* scene->sprites[count]->sprite_img->height)
				/ scene->sprites[count]->sprite_height) / 256;
		sprite_coloring(scene, count, stripe, j);
		j++;
	}
}

void	spawn_sprites(t_scene *scene, int count)
{
	int	stripe;
	int	j;

	initial_calculation(scene, count);
	line_coordinates(scene, count);
	stripe = scene->sprites[count]->start[X];
	while (stripe < scene->sprites[count]->end[X])
	{
		j = scene->sprites[count]->start[Y];
		calculate_texture_coordinates(scene, count, stripe);
		if (stripe > 0 && stripe < WIN_WIDTH
			&& scene->sprites[count]->transform[Y] > 0
			&& scene->sprites[count]->transform[Y] < scene->z_buffer[stripe])
		{
			render_vertical_lines(scene, count, stripe, j);
		}
		stripe++;
	}
}

void	sort_sprites(t_sprite **sprites, int count)
{
	int			i;
	int			j;
	t_sprite	*tmp;

	j = 0;
	i = 0;
	while (i < count)
	{
		j = 0;
		while (j < count - 1)
		{
			if (sprites[j]->sprite_distance < sprites[j + 1]->sprite_distance)
			{
				tmp = sprites[j];
				sprites[j] = sprites[j + 1];
				sprites[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

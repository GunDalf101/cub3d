/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:16:09 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/09 12:27:44 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	animation_coloring(t_scene *scene, int count, int stripe, int j)
{
	u_int8_t	r;
	u_int8_t	g;
	u_int8_t	b;
	u_int8_t	a;

	r = scene->sprites[count]->animation_img->pixels[scene->sprites[count]->\
	tex[Y] * 4 * scene->sprites[count]->animation_img->width
		+ scene->sprites[count]->tex[X] * 4];
	g = scene->sprites[count]->animation_img->pixels[scene->sprites[count]->\
	tex[Y] * 4 * scene->sprites[count]->animation_img->width
		+ scene->sprites[count]->tex[X] * 4 + 1];
	b = scene->sprites[count]->animation_img->pixels[scene->sprites[count]->\
	tex[Y] * 4 * scene->sprites[count]->animation_img->width
		+ scene->sprites[count]->tex[X] * 4 + 2];
	a = scene->sprites[count]->animation_img->pixels[scene->sprites[count]->\
	tex[Y] * 4 * scene->sprites[count]->animation_img->width
		+ scene->sprites[count]->tex[X] * 4 + 3];
	if (a < 200)
		return ;
	mlx_put_pixel(scene->mlx_img, stripe, scene->player->central_angle
		- scene->player->crouch + j, ft_pixel(r, g, b, a));
}

void	calculate_animation_coordinates(t_scene *scene, int count, int stripe)
{
	scene->sprites[count]->tex[X] = (int)(256 * (stripe
				- (-scene->sprites[count]->sprite_width / 2
					+ scene->sprites[count]->sprite_screen_x))
			* scene->sprites[count]->animation_img->width
			/ scene->sprites[count]->sprite_width) / 256;
}

void	animate_vertical_lines(t_scene *scene, int count, int stripe, int j)
{
	while (j < scene->sprites[count]->end[Y])
	{
		scene->sprites[count]->d = (j - scene->sprites[count]->v_move_screen)
			* 256 - WIN_HEIGHT * 128 + scene->sprites[count]->sprite_height
			* 128;
		scene->sprites[count]->tex[Y] = ((scene->sprites[count]->d
					* scene->sprites[count]->animation_img->height)
				/ scene->sprites[count]->sprite_height) / 256;
		animation_coloring(scene, count, stripe, j);
		j++;
	}
}

void	spawn_animations(t_scene *scene, int count)
{
	int	stripe;
	int	j;

	initial_anime_calculation(scene, count);
	animated_line_coord(scene, count);
	stripe = scene->sprites[count]->start[X];
	while (stripe < scene->sprites[count]->end[X])
	{
		j = scene->sprites[count]->start[Y];
		calculate_animation_coordinates(scene, count, stripe);
		if (stripe > 0 && stripe < WIN_WIDTH
			&& scene->sprites[count]->transform[Y] > 0
			&& scene->sprites[count]->transform[Y] < scene->z_buffer[stripe])
		{
			animate_vertical_lines(scene, count, stripe, j);
		}
		stripe++;
	}
}

void	animated_sprite(t_scene scene, int i)
{
	static int	frame;

	if (frame >= 15000)
		frame = 0;
	scene.sprites[i]->animation_img = scene.evil_warlock[frame / 1500];
	spawn_animations(&scene, i);
	frame++;
}

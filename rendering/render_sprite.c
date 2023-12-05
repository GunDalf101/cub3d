/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:17:02 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/05 20:08:44 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	initial_calculation(t_scene *scene, int count)
{
	scene->sprites[count]->relative_pos[Y] = scene->sprites[count]->pos[Y]
		- scene->player->pos[Y];
	scene->sprites[count]->relative_pos[X] = scene->sprites[count]->pos[X]
		- scene->player->pos[X];
	scene->sprites[count]->inverse_det = 1.0 / (scene->player->plane[Y]
			* scene->player->dir[X] - scene->player->dir[Y]
			* scene->player->plane[X]);
	scene->sprites[count]->transform[Y] = scene->sprites[count]->inverse_det
		* (-scene->player->plane[X] * scene->sprites[count]->relative_pos[Y]
			+ scene->player->plane[Y] * scene->sprites[count]->relative_pos[X]);
	scene->sprites[count]->transform[X] = scene->sprites[count]->inverse_det
		* (scene->player->dir[X] * scene->sprites[count]->relative_pos[Y]
			- scene->player->dir[Y] * scene->sprites[count]->relative_pos[X]);
	scene->sprites[count]->v_move_screen = (int)(scene->sprites[count]->v_move
			/ scene->sprites[count]->transform[Y]);
	scene->sprites[count]->sprite_screen_x = (int)((WIN_WIDTH / 2) * (1
				+ scene->sprites[count]->transform[X]
				/ scene->sprites[count]->transform[Y]));
	scene->sprites[count]->sprite_height = abs((int)(scene->sprites[count]->\
		sprite_img->height / (scene->sprites[count]->transform[Y]) * 7));
}

void	line_coordinates(t_scene *scene, int count)
{
	scene->sprites[count]->start[Y] = -scene->sprites[count]->sprite_height / 2
		+ WIN_HEIGHT / 2 + scene->sprites[count]->v_move_screen;
	if (scene->sprites[count]->start[Y] < -scene->player->central_angle
		+ scene->player->crouch)
		scene->sprites[count]->start[Y] = -scene->player->central_angle
			+ scene->player->crouch;
	scene->sprites[count]->end[Y] = scene->sprites[count]->sprite_height / 2
		+ WIN_HEIGHT / 2 + scene->sprites[count]->v_move_screen;
	if (scene->sprites[count]->end[Y] >= WIN_HEIGHT
		- scene->player->central_angle + scene->player->crouch)
		scene->sprites[count]->end[Y] = WIN_HEIGHT
			- scene->player->central_angle + scene->player->crouch - 1;
	scene->sprites[count]->sprite_width = abs((int)(scene->sprites[count]->\
		sprite_img->width / (scene->sprites[count]->transform[Y]) * 7));
	scene->sprites[count]->start[X] = scene->sprites[count]->sprite_screen_x
		- scene->sprites[count]->sprite_width / 2;
	if (scene->sprites[count]->start[X] < 0)
		scene->sprites[count]->start[X] = 0;
	scene->sprites[count]->end[X] = scene->sprites[count]->sprite_screen_x
		+ scene->sprites[count]->sprite_width / 2;
	if (scene->sprites[count]->end[X] >= WIN_WIDTH)
		scene->sprites[count]->end[X] = WIN_WIDTH - 1;
}

void	sprite_coloring(t_scene *scene, int count, int stripe, int j)
{
	u_int8_t	r;
	u_int8_t	g;
	u_int8_t	b;
	u_int8_t	a;

	r = scene->sprites[count]->sprite_img->pixels[scene->sprites[count]->tex[Y]
		* 4 * scene->sprites[count]->sprite_img->width
		+ scene->sprites[count]->tex[X] * 4];
	g = scene->sprites[count]->sprite_img->pixels[scene->sprites[count]->tex[Y]
		* 4 * scene->sprites[count]->sprite_img->width
		+ scene->sprites[count]->tex[X] * 4 + 1];
	b = scene->sprites[count]->sprite_img->pixels[scene->sprites[count]->tex[Y]
		* 4 * scene->sprites[count]->sprite_img->width
		+ scene->sprites[count]->tex[X] * 4 + 2];
	a = scene->sprites[count]->sprite_img->pixels[scene->sprites[count]->tex[Y]
		* 4 * scene->sprites[count]->sprite_img->width
		+ scene->sprites[count]->tex[X] * 4 + 3];
	if (a < 200)
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

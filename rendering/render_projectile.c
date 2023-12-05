/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_projectile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:18:18 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/05 19:51:11 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	init_calc(t_scene *scene, t_projectile *projectile)
{
	projectile->relative_pos[Y] = projectile->pos[Y] - scene->player->pos[Y];
	projectile->relative_pos[X] = projectile->pos[X] - scene->player->pos[X];
	projectile->inverse_det = 1.0 / (scene->player->plane[Y]
			* scene->player->dir[X] - scene->player->dir[Y]
			* scene->player->plane[X]);
	projectile->transform[Y] = projectile->inverse_det
		* (-scene->player->plane[X] * projectile->relative_pos[Y]
			+ scene->player->plane[Y] * projectile->relative_pos[X]);
	projectile->transform[X] = projectile->inverse_det * (scene->player->dir[X]
			* projectile->relative_pos[Y] - scene->player->dir[Y]
			* projectile->relative_pos[X]);
	projectile->v_move_screen = (int)(projectile->v_move
			/ projectile->transform[Y]);
	projectile->proj_screen_x = (int)((WIN_WIDTH / 2) * (1
				+ projectile->transform[X] / projectile->transform[Y]));
	projectile->proj_height = abs((int)(projectile->proj_img->height
				/ (projectile->transform[Y]) * 7));
}

void	linear_coords(t_scene *scene, t_projectile *projectile)
{
	projectile->start[Y] = -projectile->proj_height / 2 + WIN_HEIGHT / 2
		+ projectile->v_move_screen;
	if (projectile->start[Y] < -scene->player->central_angle
		+ scene->player->crouch)
		projectile->start[Y] = -scene->player->central_angle
			+ scene->player->crouch;
	projectile->end[Y] = projectile->proj_height / 2 + WIN_HEIGHT / 2
		+ projectile->v_move_screen;
	if (projectile->end[Y] >= WIN_HEIGHT - scene->player->central_angle
		+ scene->player->crouch)
		projectile->end[Y] = WIN_HEIGHT - scene->player->central_angle
			+ scene->player->crouch - 1;
	projectile->proj_width = abs((int)(projectile->proj_img->width
				/ (projectile->transform[Y]) * 7));
	projectile->start[X] = projectile->proj_screen_x - projectile->proj_width
		/ 2;
	if (projectile->start[X] < 0)
		projectile->start[X] = 0;
	projectile->end[X] = projectile->proj_screen_x + projectile->proj_width / 2;
	if (projectile->end[X] >= WIN_WIDTH)
		projectile->end[X] = WIN_WIDTH - 1;
}

void	projectile_coloring(t_scene *scene, t_projectile *projectile,
		int stripe, int j)
{
	u_int8_t	r;
	u_int8_t	g;
	u_int8_t	b;
	u_int8_t	a;

	projectile->d = (j - projectile->v_move_screen) * 256 - WIN_HEIGHT * 128
		+ projectile->proj_height * 128;
	projectile->tex[Y] = ((projectile->d * projectile->proj_img->height)
			/ projectile->proj_height) / 256;
	r = projectile->proj_img->pixels[projectile->tex[Y] * 4
		* projectile->proj_img->width + projectile->tex[X] * 4];
	g = projectile->proj_img->pixels[projectile->tex[Y] * 4
		* projectile->proj_img->width + projectile->tex[X] * 4 + 1];
	b = projectile->proj_img->pixels[projectile->tex[Y] * 4
		* projectile->proj_img->width + projectile->tex[X] * 4 + 2];
	a = projectile->proj_img->pixels[projectile->tex[Y] * 4
		* projectile->proj_img->width + projectile->tex[X] * 4 + 3];
	if (a < 255)
		return ;
	mlx_put_pixel(scene->mlx_img, stripe, scene->player->central_angle
		- scene->player->crouch + j, ft_pixel(r, g, b, a));
}

void	spawn_proj(t_scene *scene, t_projectile *projectile)
{
	int	stripe;
	int	j;

	init_calc(scene, projectile);
	linear_coords(scene, projectile);
	stripe = projectile->start[X];
	while (stripe < projectile->end[X])
	{
		projectile->tex[X] = (int)(256 * (stripe - (-projectile->proj_width / 2
						+ projectile->proj_screen_x))
				* projectile->proj_img->width / projectile->proj_width) / 256;
		if (stripe > 0 && stripe < WIN_WIDTH && projectile->transform[Y] > 0
			&& projectile->transform[Y] < scene->z_buffer[stripe])
		{
			j = projectile->start[Y];
			while (j < projectile->end[Y])
			{
				projectile_coloring(scene, projectile, stripe, j);
				j++;
			}
		}
		stripe++;
	}
}

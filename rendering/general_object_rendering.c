/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_object_rendering.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:11:32 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/07 11:20:33 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	drawbar(t_scene scene)
{
	t_dda	dda;
	int		i;
	int		healthbar;
	int		manabar;

	i = 0;
	healthbar = scene.player->health_points * 2;
	manabar = scene.player->mana_points * 2;
	while (i < 20 && healthbar > 0)
	{
		dda.x1 = 50;
		dda.y1 = i + WIN_HEIGHT - 60;
		dda.color = 0xFF0000FF;
		drawline(&dda, 50 + healthbar, i + WIN_HEIGHT - 60, scene);
		i++;
	}
	i = 0;
	while (i < 20 && manabar > 0)
	{
		dda.x1 = 50;
		dda.y1 = i + WIN_HEIGHT - 35;
		dda.color = 0x0000FFFF;
		drawline(&dda, 50 + manabar, i + WIN_HEIGHT - 35, scene);
		i++;
	}
}

void	sky_floor_render(t_scene scene)
{
	t_dda	dda;
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (i++ < scene.player->central_angle + WIN_HEIGHT / 2
		- scene.player->crouch)
	{
		dda.x1 = 0;
		dda.y1 = i;
		dda.color = scene.map->ceiling_rgb[0] << 24 | scene.map->\
		ceiling_rgb[1] << 16 | scene.map->ceiling_rgb[2] << 8 | 255;
		drawline(&dda, WIN_WIDTH, i, scene);
	}
	i = scene.player->central_angle + WIN_HEIGHT / 2 - scene.player->crouch;
	while (i++ < WIN_HEIGHT)
	{
		dda.x1 = 0;
		dda.y1 = i;
		dda.color = scene.map->floor_rgb[0] << 24 | scene.map->\
		floor_rgb[1] << 16 | scene.map->floor_rgb[2] << 8 | 255;
		drawline(&dda, WIN_WIDTH, i, scene);
		i++;
	}
}

void	draw_death(t_scene scene, t_death *death, mlx_image_t *death_img)
{
	death->r = death_img->pixels[death->i * 4 * death_img->width + death->j
		* 4];
	death->g = death_img->pixels[death->i * 4 * death_img->width + death->j * 4
		+ 1];
	death->b = death_img->pixels[death->i * 4 * death_img->width + death->j * 4
		+ 2];
	death->a = death_img->pixels[death->i * 4 * death_img->width + death->j * 4
		+ 3];
	if (death->a == 0)
		return ;
	mlx_put_pixel(scene.mlx_img, death->j + WIN_WIDTH / 2 - death_img->width
		/ 2, death->i + WIN_HEIGHT / 2 - death_img->height / 2,
		ft_pixel(death->r, death->g, death->b, death->a));
}

void	death_screen(t_scene scene)
{
	mlx_texture_t	*death_screen;
	mlx_image_t		*death_img;
	t_death			death;

	death_screen = mlx_load_png("assets/DEAD.png");
	death_img = mlx_texture_to_image(scene.mlx_ptr, death_screen);
	mlx_delete_texture(death_screen);
	death.i = 0;
	while (death.i++ < death_img->height)
	{
		death.j = 0;
		while (death.j++ < death_img->width)
		{
			draw_death(scene, &death, death_img);
		}
	}
	mlx_delete_image(scene.mlx_ptr, death_img);
}

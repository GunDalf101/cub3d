/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:07:21 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/15 12:28:54 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	minimap_init(t_minimap *minimap, t_scene *scene)
{
	minimap->player_pos_x = (double)((scene->player->pos[Y]) / UNIT);
	minimap->player_pos_y = (double)((scene->player->pos[X]) / UNIT);
	minimap->i = minimap->player_pos_x - 2.5;
	minimap->j = minimap->player_pos_y - 2.5;
	minimap->pos_x = 0;
	minimap->pos_y = 0;
	minimap->k = -0.5;
	minimap->l = -0.5;
	minimap->o_x = 0;
	minimap->o_y = 0;
}

void	minimap_coloring(t_minimap *minimap, t_scene *scene)
{
	double	distance_squared;

	distance_squared = pow(minimap->pos_x - minimap->o_x, 2)
		+ pow(minimap->pos_y - minimap->o_y, 2);
	if ((minimap->i < 0 || minimap->j < 0 || minimap->i >= scene->map->map_width
			|| minimap->j >= scene->map->map_height)
		&& distance_squared <= 10000)
		mlx_put_pixel(scene->mlx_img, minimap->pos_x, minimap->pos_y,
			0x00000000);
	else if (distance_squared <= 10000
		&& scene->map->map[(int)(minimap->j)][(int)(minimap->i)] == '1')
		mlx_put_pixel(scene->mlx_img, minimap->pos_x, minimap->pos_y,
			0x000000FF);
	else if (distance_squared <= 10000
		&& scene->map->map[(int)(minimap->j)][(int)(minimap->i)] == 'T')
		mlx_put_pixel(scene->mlx_img, minimap->pos_x, minimap->pos_y,
			0xFF4E01FF);
	else if (distance_squared <= 10000
		&& (scene->map->map[(int)(minimap->j)][(int)(minimap->i)] == 'C'))
		mlx_put_pixel(scene->mlx_img, minimap->pos_x, minimap->pos_y,
			0xCD7F32FF);
	else if (distance_squared <= 10000
		&& scene->map->map[(int)(minimap->j)][(int)(minimap->i)] != '1')
		mlx_put_pixel(scene->mlx_img, minimap->pos_x, minimap->pos_y,
			0x9b7653FF);
}

void	draw_minimap_circle(t_scene *scene)
{
	t_minimap	minimap;

	minimap_init(&minimap, scene);
	while (minimap.i < minimap.player_pos_x + 2.5)
	{
		minimap.j = minimap.player_pos_y - 2.5;
		minimap.k = -0.5;
		while (minimap.j < minimap.player_pos_y + 2.5)
		{
			minimap.pos_x = (minimap.l * 60 + 60 / 2);
			minimap.pos_y = (minimap.k * 60 + 60 / 2);
			minimap.o_x = 1.499999 * UNIT / 3 + UNIT / 2;
			minimap.o_y = 1.499999 * UNIT / 3 + UNIT / 2;
			minimap_coloring(&minimap, scene);
			minimap.j += MINIMAP_SCALE_FACTOR;
			minimap.k += 1.0 / UNIT;
		}
		minimap.i += MINIMAP_SCALE_FACTOR;
		minimap.l += 1.0 / UNIT;
	}
	minimap.dda.x1 = minimap.o_x;
	minimap.dda.y1 = minimap.o_y;
	minimap.dda.color = 0x00FF00FF;
	drawline(&minimap.dda, (minimap.o_x + scene->player->dir[Y] / 2),
		(minimap.o_y + scene->player->dir[X] / 2), *scene);
}

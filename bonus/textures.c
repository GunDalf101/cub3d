/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:46:46 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/14 05:44:37 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static t_direction	get_wall_dir(t_player *player, int x)
{
	if (player->vision_rays[x]->side == EW)
	{
		if (player->vision_rays[x]->dir[Y] < 0)
			return (WEST);
		else
			return (EAST);
	}
	else if (player->vision_rays[x]->dir[X] < 0)
		return (NORTH);
	return (SOUTH);
}

static mlx_image_t	*get_texture(t_scene *scene, t_ray_caster *wizard)
{
	if (scene->map->map[scene->player->vision_rays[wizard->x]->current_cell[X]
			/ UNIT][scene->player->vision_rays[wizard->x]->current_cell[Y]
		/ UNIT] == 'D')
		return (scene->door_img);
	else if (scene->map->map[scene->player->vision_rays[wizard->x]->\
			current_cell[X]
			/ UNIT][scene->player->vision_rays[wizard->x]->current_cell[Y]
		/ UNIT] == 'L')
		return (scene->end_img);
	else
		return (scene->map->textures_mlx_imgs[get_wall_dir(scene->player,
					wizard->x)]);
}

static void	draw_pixel(t_scene *scene, t_ray_caster *wizard, mlx_image_t *wtext, long long iy)
{
	int	i;
	int	y;

	i = (int)(iy & 0xFFFFFFFF);
    y = (int)((iy >> 32) & 0xFFFFFFFF);
	mlx_put_pixel(scene->mlx_img, wizard->x, wizard->linestart,
			ft_pixel(wtext->pixels[(int)y * wtext->width * 4 + i * 4]
				* wizard->intensity, wtext->pixels[(int)y * wtext->width * 4 + i
				* 4 + 1] * wizard->intensity, wtext->pixels[(int)y
				* wtext->width * 4 + i * 4 + 2] * wizard->intensity,
				wtext->pixels[(int)y * wtext->width * 4 + i * 4 + 3]));
}

static int	get_index(t_scene *scene, t_ray_caster *wizard)
{
	t_direction	wdir;
	int			i;

	wdir = get_wall_dir(scene->player, wizard->x);
	if (wdir == EAST || wdir == WEST)
		i = scene->player->vision_rays[wizard->x]->\
		current_cell[X] % UNIT;
	else
		i = scene->player->vision_rays[wizard->x]->\
		current_cell[Y] % UNIT;
	return (i);
}

void	drawline_from_textures(t_scene *scene, t_ray_caster *wizard)
{
	int			i;
	mlx_image_t	*wtext;
	double		wh;
	double		y;

	wtext = get_texture(scene, wizard);
	i = get_index(scene, wizard);
	i *= (wtext->width / UNIT);
	wh = wizard->trueend - wizard->truestart;
	wh = wtext->height / wh;
	y = abs(wizard->truestart - wizard->linestart) * wh;
	wizard->intensity = 1 / (scene->player->vision_rays[wizard->x]->wall_dist
			* 0.03 + 1);
	while (wizard->linestart < wizard->lineend)
	{
		draw_pixel(scene, wizard, wtext, ((uint64_t)i << 32) | (uint64_t)y);
		wizard->linestart++;
		y += wh;
	}
}

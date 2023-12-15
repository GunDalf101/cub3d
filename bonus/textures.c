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

static void	perror_faulty_texuture(char *fpath)
{
	printf("could not load texture: [%s]\n", fpath);
	exit(1);
}

int	load_textures(void *mlxptr, t_map *map)
{
	int				i;
	mlx_texture_t	*texture;

	map->textures_mlx_imgs = malloc(sizeof(mlx_image_t *) * 4);
	if (!map->textures_mlx_imgs)
		return (1);
	i = 0;
	while (i < 4)
	{
		texture = mlx_load_png(map->textures_paths[i]);
		if (!texture)
			perror_faulty_texuture(map->textures_paths[i]);
		map->textures_mlx_imgs[i] = mlx_texture_to_image(mlxptr, texture);
		if (!map->textures_mlx_imgs[i])
			perror_faulty_texuture(map->textures_paths[i]);
		mlx_resize_image(map->textures_mlx_imgs[i], WIN_WIDTH, WIN_WIDTH);
		mlx_delete_texture(texture);
		i++;
	}
	return (0);
}

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

void	drawline_from_textures(t_scene *scene, t_ray_caster *wizard)
{
	t_direction	wdir;
	int			i;
	mlx_image_t	*wtext;
	double		wh;
	double		y;

	wdir = get_wall_dir(scene->player, wizard->x);
	wtext = get_texture(scene, wizard);
	if (wdir == EAST || wdir == WEST)
		i = scene->player->vision_rays[wizard->x]->current_cell[X] % UNIT;
	else
		i = scene->player->vision_rays[wizard->x]->current_cell[Y] % UNIT;
	i = wtext->width / UNIT * i;
	wh = wizard->trueend - wizard->truestart;
	wh = wtext->height / wh;
	y = abs(wizard->truestart - wizard->linestart) * wh;
	wizard->intensity = 1 / (scene->player->vision_rays[wizard->x]->wall_dist
			* 0.03 + 1);
	while (wizard->linestart < wizard->lineend)
	{
		mlx_put_pixel(scene->mlx_img, wizard->x, wizard->linestart,
			ft_pixel(wtext->pixels[(int)y * wtext->width * 4 + i * 4]
				* wizard->intensity, wtext->pixels[(int)y * wtext->width * 4 + i
				* 4 + 1] * wizard->intensity, wtext->pixels[(int)y
				* wtext->width * 4 + i * 4 + 2] * wizard->intensity,
				wtext->pixels[(int)y * wtext->width * 4 + i * 4 + 3]));
		wizard->linestart++;
		y += wh;
	}
}
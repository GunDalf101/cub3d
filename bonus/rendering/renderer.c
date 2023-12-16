/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:16:36 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/16 00:20:21 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	sprites_only(t_scene scene)
{
	int				i;
	static float	frame;

	if (frame >= 40)
		frame = 0;
	i = 0;
	while (i < scene.sprite_count)
	{
		if (scene.sprites[i]->animation_img)
			animated_sprite(scene, i, (int)frame);
		else
			spawn_sprites(&scene, i);
		i++;
	}
	frame += 1 / (scene.frame_time * 35);
}

void	sprites_projectiles(t_scene scene)
{
	int				i;
	t_projectile	*tmp;

	i = 0;
	while (i < scene.sprite_count)
	{
		scene.sprites[i]->sprite_distance = sqrt(pow(scene.sprites[i]->pos[Y]
					- scene.player->pos[Y], 2) + pow(scene.sprites[i]->pos[X]
					- scene.player->pos[X], 2));
		i++;
	}
	sort_sprites(scene.sprites, scene.sprite_count);
	sprites_only(scene);
	tmp = scene.projectiles;
	while (tmp)
	{
		spawn_proj(&scene, tmp);
		tmp = tmp->next;
	}
}

void	drawscore(t_scene scene)
{
	t_death	death;

	if (!scene.score_img)
		return ;
	death.i = 0;
	while (death.i++ < scene.score_img->height)
	{
		death.j = 0;
		while (death.j++ < scene.score_img->width)
		{
			death.r = scene.score_img->pixels[death.i * 4
				* scene.score_img->width + death.j * 4];
			death.g = scene.score_img->pixels[death.i * 4
				* scene.score_img->width + death.j * 4 + 1];
			death.b = scene.score_img->pixels[death.i * 4
				* scene.score_img->width + death.j * 4 + 2];
			death.a = scene.score_img->pixels[death.i * 4
				* scene.score_img->width + death.j * 4 + 3];
			if (death.a == 0)
				continue ;
			mlx_put_pixel(scene.mlx_img, death.j + WIN_WIDTH - 160, death.i
				+ 20, ft_pixel(death.r, death.g, death.b, death.a));
		}
	}
}

void	load_score(t_scene *scene)
{
	char	*score;
	char	*score_str;

	score = ft_itoa(scene->score);
	score_str = ft_strjoin("Score: ", score);
	scene->score_img = mlx_put_string(scene->mlx_ptr, score_str, WIN_WIDTH
			- 160, 20);
	free(score);
	free(score_str);
}

void	renderitall(t_scene scene)
{
	(void)scene;
	if (scene.win != TRUE)
	{
		ray_caster(&scene);
		sprites_projectiles(scene);
		draw_attack(&scene);
	}
	if (scene.win == TRUE)
	{
		draw_ending(scene);
		sleep(1);
		win_screen(scene);
	}
	draw_minimap_circle(&scene);
	drawbar(scene);
	load_score(&scene);
	drawscore(scene);
	load_timer(&scene);
	drawtimer(scene);
	if (scene.player->is_ded == TRUE)
		death_screen(scene);
	mlx_image_to_window(scene.mlx_ptr, scene.mlx_img, 0, 0);
	if (scene.win != TRUE)
		occasional_free(&scene);
}

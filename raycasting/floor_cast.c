/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_cast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:46:30 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/06 17:18:02 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"
#include <float.h>
#include <iso646.h>

void    floor_casting(t_scene *scene){
	int		x;
	x = WIN_HEIGHT / 2 - scene->player->crouch + scene->player->central_angle;
	while (x < WIN_HEIGHT)
	{
		double ray_dir_x0 = scene->player->dir[X] - scene->player->plane[X];
        double ray_dir_y0 = scene->player->dir[Y] - scene->player->plane[Y];
        double ray_dir_x1 = scene->player->dir[X] + scene->player->plane[X];
        double ray_dir_y1 = scene->player->dir[Y] + scene->player->plane[Y];
        
        int p = x - WIN_HEIGHT;
        double ray_pos_z = 0.5 * WIN_HEIGHT;
        double row_distance = ray_pos_z / p;

        double floor_step_x = row_distance * (ray_dir_x1 - ray_dir_x0) / WIN_WIDTH;
        double floor_step_y = row_distance * (ray_dir_y1 - ray_dir_y0) / WIN_WIDTH;
        double floor_x = row_distance * ray_dir_x0 + scene->player->pos[X] / 3;
        double floor_y = row_distance * ray_dir_y0 + scene->player->pos[Y] / 3;
        int y = 0;
        while (y < WIN_WIDTH)
        {
            double current_dist = WIN_WIDTH / (2.0 * (x + scene->player->crouch - scene->player->central_angle) - WIN_WIDTH);
            double weight = current_dist / row_distance;
            double current_floor_x = weight * floor_x + (1.0 - weight) * scene->player->pos[X] / 3;
            double current_floor_y = weight * floor_y + (1.0 - weight) * scene->player->pos[Y] / 3;
            int tx = (int)(scene->map->textures_mlx_imgs[0]->width * (current_floor_x) / 33.5) % scene->map->textures_mlx_imgs[0]->width;
            int ty = (int)(scene->map->textures_mlx_imgs[0]->height * (current_floor_y) / 33.5) % scene->map->textures_mlx_imgs[0]->height;
            floor_x += floor_step_x;
            floor_y += floor_step_y;
            int color = ft_pixel(scene->map->textures_mlx_imgs[0]->pixels[scene->map->textures_mlx_imgs[0]->width * ty * 4 + tx * 4], scene->map->textures_mlx_imgs[0]->pixels[scene->map->textures_mlx_imgs[0]->width * ty * 4 + tx * 4 + 1], scene->map->textures_mlx_imgs[0]->pixels[scene->map->textures_mlx_imgs[0]->width * ty * 4 + tx * 4 + 2], scene->map->textures_mlx_imgs[0]->pixels[scene->map->textures_mlx_imgs[0]->width * ty * 4 + tx * 4 + 3]);
            if (current_floor_y / 34.25 + scene->player->pos[Y] / (UNIT * 34.25) > 0 && current_floor_x / 34.25  + scene->player->pos[X] / (UNIT * 34.25) > 0 && current_floor_y / 34.25 + scene->player->pos[Y] / (UNIT * 34.25) < scene->map->map_width && current_floor_x / 34.25  + scene->player->pos[X] / (UNIT * 34.25) < scene->map->map_height && scene->map->map[(int)(current_floor_x / 34.25 + scene->player->pos[X] / (UNIT * 34.25))][(int)(current_floor_y / 34.25 + scene->player->pos[Y] / (UNIT * 34.25))] == 'T')
            {
                color = ft_pixel(scene->map->textures_mlx_imgs[2]->pixels[scene->map->textures_mlx_imgs[2]->width * ty * 4 + tx * 4], scene->map->textures_mlx_imgs[2]->pixels[scene->map->textures_mlx_imgs[2]->width * ty * 4 + tx * 4 + 1], scene->map->textures_mlx_imgs[2]->pixels[scene->map->textures_mlx_imgs[2]->width * ty * 4 + tx * 4 + 2], scene->map->textures_mlx_imgs[2]->pixels[scene->map->textures_mlx_imgs[2]->width * ty * 4 + tx * 4 + 3]);
            }
            mlx_put_pixel(scene->mlx_img, y ,x, color);
            // current_dist = WIN_WIDTH / (2.0 * (x + scene->player->crouch - scene->player->central_angle) + WIN_WIDTH);
            // color = ft_pixel(scene->map->textures_mlx_imgs[2]->pixels[scene->map->textures_mlx_imgs[2]->width * ty * 4 + tx * 4], scene->map->textures_mlx_imgs[2]->pixels[scene->map->textures_mlx_imgs[2]->width * ty * 4 + tx * 4 + 1], scene->map->textures_mlx_imgs[2]->pixels[scene->map->textures_mlx_imgs[2]->width * ty * 4 + tx * 4 + 2], scene->map->textures_mlx_imgs[2]->pixels[scene->map->textures_mlx_imgs[2]->width * ty * 4 + tx * 4 + 3]);
            // mlx_put_pixel(scene->mlx_img, y, WIN_HEIGHT - x - 1, color);
            y++;
        }
		x++;
	}
}

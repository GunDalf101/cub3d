/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousebinds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:37:15 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/15 10:54:51 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	angle_update(t_scene *scene)
{
	if (scene->player->p_angle < 0)
		scene->player->p_angle += 2 * M_PI;
	if (scene->player->p_angle > 2 * M_PI)
		scene->player->p_angle -= 2 * M_PI;
	if (scene->player->central_angle > WIN_HEIGHT / 2)
		scene->player->central_angle = WIN_HEIGHT / 2;
	if (scene->player->central_angle < -WIN_HEIGHT / 3)
		scene->player->central_angle = -WIN_HEIGHT / 3;
}

void	hookercur(double xpos, double ypos, void *scene2)
{
	t_scene			*scene;
	static double	old_ypos;
	static double	old_xpos;

	scene = (t_scene *)scene2;
	if (scene->win || scene->player->is_ded)
		return ;
	if (old_ypos == 0)
	{
		old_ypos = ypos;
		old_xpos = scene->player->p_angle;
	}
	scene->player->p_angle = xpos / 80 + old_xpos;
	if (old_ypos < ypos)
		scene->player->central_angle -= 70.0;
	else if (old_ypos > ypos)
		scene->player->central_angle += 70.0;
	angle_update(scene);
	scene->player->dir[Y] = (double)cos(scene->player->p_angle) * 25;
	scene->player->dir[X] = (double)sin(scene->player->p_angle) * 25;
	scene->player->plane[Y] = (double)cos(scene->player->p_angle + M_PI_2)
		* 16.5;
	scene->player->plane[X] = (double)sin(scene->player->p_angle + M_PI_2)
		* 16.5;
	old_ypos = ypos;
}

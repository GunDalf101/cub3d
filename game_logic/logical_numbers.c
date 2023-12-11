/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_numbers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:31:24 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/11 20:39:17 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	check_win(t_scene *scene)
{
	static int	i;

	if (scene->map->map[(int)(scene->player->pos[X])
		/ UNIT][(int)(scene->player->pos[Y]) / UNIT] == 'L')
	{
		if (i == 0)
			system("afplay assets/win.mp3 & (sleep 20\
             && pkill afplay && exit) &");
		scene->win = TRUE;
	}
	if (scene->win == TRUE)
		i++;
}

void	check_timer(t_scene *scene)
{
	int		time;

	if (scene->win)
		return ;
	time = mlx_get_time() - scene->timer.time_origin;
	scene->timer.hours = time / 3600;
	time %= 3600;
	scene->timer.minutes = time / 60;
	time %= 60;
	scene->timer.seconds = time;
}

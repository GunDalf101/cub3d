/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_logic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:54:20 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/11 10:41:10 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	check_player_health(t_scene *scene)
{
	if (scene->player->health_points <= 0)
		scene->player->is_ded = TRUE;
}

void	check_trapped(t_scene *scene)
{
	if (scene->map->map[(int)(scene->player->pos[X])
		/ UNIT][(int)(scene->player->pos[Y]) / UNIT] == 'T'
		&& scene->player->health_points > 0)
		scene->player->is_trapped += TRUE;
	else
		scene->player->is_trapped = FALSE;
}

void	update_sprite_positions(t_scene *scene)
{
	int	i;

	i = 0;
	while (scene->sprites[i])
	{
		if ((int)(scene->player->pos[X])
			/ UNIT == (int)(scene->sprites[i]->pos[X]) / UNIT
			&& (int)(scene->player->pos[Y])
			/ UNIT == (int)(scene->sprites[i]->pos[Y]) / UNIT)
		{
			scene->sprites[i]->pos[X] = -UNIT;
			scene->sprites[i]->pos[Y] = -UNIT;
			break ;
		}
		i++;
	}
}

void	restore_mana(t_scene *scene)
{
	if (scene->map->map[(int)(scene->player->pos[X])
		/ UNIT][(int)(scene->player->pos[Y]) / UNIT] == 'M')
	{
		system("afplay assets/restoreMana.mp3 &");
		if (scene->player->mana_points + 10 > UNIT)
			scene->player->mana_points = UNIT;
		else
			scene->player->mana_points += 10;
		update_sprite_positions(scene);
		scene->map->map[(int)(scene->player->pos[X])
			/ UNIT][(int)(scene->player->pos[Y]) / UNIT] = '0';
	}
}

void	check_win(t_scene *scene)
{
	static int	i;

	if (scene->map->map[(int)(scene->player->pos[X])
		/ UNIT][(int)(scene->player->pos[Y]) / UNIT] == 'L')
	{
		if (i == 0)
			system("afplay assets/win.mp3 &");
		scene->win = TRUE;
	}
	if (scene->win == TRUE)
		i++;
	if (i == 200)
		exit(0);
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

void	dynamic_logic(t_scene *scene)
{
	check_timer(scene);
	check_player_health(scene);
	check_trapped(scene);
	restore_mana(scene);
	check_win(scene);
}

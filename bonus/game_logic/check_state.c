/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 22:45:09 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/15 11:01:40 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	is_player_close_for_attack(const t_player *player, const t_sprite *enemy)
{
	return (player->pos[X] + 50 > enemy->pos[X] && player->pos[X]
		- 50 < enemy->pos[X] && player->pos[Y] + 50 > enemy->pos[Y]
		&& player->pos[Y] - 50 < enemy->pos[Y]);
}

int	is_player_in_range_for_pursuit(const t_player *player,
		const t_sprite *enemy, const t_dda *dda, const t_scene *scene)
{
	return (player->pos[X] + 8 * UNIT > enemy->pos[X] && player->pos[X] - 8
		* UNIT < enemy->pos[X] && player->pos[Y] + 8 * UNIT > enemy->pos[Y]
		&& player->pos[Y] - 8 * UNIT < enemy->pos[Y] && line_o_sight(*dda,
			enemy->pos[X], enemy->pos[Y], *scene));
}

void	set_enemy_state(t_sprite *enemy, int is_attack, int is_pursuit)
{
	if (is_attack)
		enemy->state = ATTACK;
	else if (is_pursuit)
		enemy->state = PURSUIT;
	else
		enemy->state = IDLE;
}

void	check_enemy_state(t_scene *scene)
{
	int		i;
	t_dda	player_dda;
	int		is_attack;
	int		is_pursuit;

	i = 0;
	player_dda.x1 = scene->player->pos[X];
	player_dda.y1 = scene->player->pos[Y];
	while (i < scene->sprite_count)
	{
		if (scene->sprites[i]->sprite_type == WARLOCK
			&& scene->sprites[i]->state != DEAD)
		{
			scene->war_index = i;
			is_attack = is_player_close_for_attack(scene->player,
					scene->sprites[i]);
			is_pursuit = is_player_in_range_for_pursuit(scene->player,
					scene->sprites[i], &player_dda, scene);
			set_enemy_state(scene->sprites[i], is_attack, is_pursuit);
			state_machine(scene, i);
		}
		i++;
	}
}

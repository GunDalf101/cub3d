/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_loading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 23:22:01 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/10 23:23:05 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	free_and_null(char **str)
{
	free(*str);
	*str = NULL;
}

char	*format_time(int time_value)
{
	char	*formatted_time;
	char	*padded_time;

	formatted_time = ft_itoa(time_value);
	if (time_value < 10)
	{
		padded_time = ft_strjoin("0", formatted_time);
		free_and_null(&formatted_time);
		formatted_time = padded_time;
	}
	return (formatted_time);
}

char	*format_and_concatenate(char *prefix, int time)
{
	char	*time_str;
	char	*result;

	time_str = format_time(time);
	result = ft_strjoin(prefix, time_str);
	free_and_null(&time_str);
	return (result);
}

char	*create_time_string(t_scene *scene)
{
	char	*hours_str;
	char	*minutes_str;
	char	*seconds_str;
	char	*time_str;
	char	*tmp;

	hours_str = format_and_concatenate("Time: ", scene->timer.hours);
	minutes_str = format_and_concatenate(":", scene->timer.minutes);
	seconds_str = format_and_concatenate(":", scene->timer.seconds);
	tmp = ft_strjoin(minutes_str, seconds_str);
	time_str = ft_strjoin(hours_str, tmp);
	free_and_null(&tmp);
	free_and_null(&hours_str);
	free_and_null(&minutes_str);
	free_and_null(&seconds_str);
	return (time_str);
}

void	load_timer(t_scene *scene)
{
	char	*time_str;

	time_str = create_time_string(scene);
	scene->timer.timer_img = mlx_put_string(scene->mlx_ptr, time_str, WIN_WIDTH
			- 160, WIN_HEIGHT - 40);
	free_and_null(&time_str);
}

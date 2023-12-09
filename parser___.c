/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser___.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 03:33:29 by hbouhach          #+#    #+#             */
/*   Updated: 2023/12/08 03:33:31 by hbouhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	close_temp_fds(int tfds[4])
{
	int	i;

	i = 0;
	while (i < 4)
		close(tfds[i++]);
	return (0);
}

int	str_starts_with(char *str, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != str[i])
			return (0);
		i++;
	}
	return (1);
}

int	pad_map(t_map *map)
{
	int		len;
	int		i;
	int		j;
	char	*l;

	i = 0;
	while (map->map[i])
	{
		l = malloc(map->map_width + 1);
		if (!l)
			return (1);
		len = ft_strlen(map->map[i]);
		j = 0;
		while (j < map->map_width)
		{
			if (j < len)
				l[j] = map->map[i][j];
			else
				l[j] = ' ';
			j++;
		}
		l[map->map_width] = '\0';
		map->map[(free(map->map[i]), i++)] = l;
	}
	return (0);
}

int	*init_stuff(char **ll, int *i)
{
	int	*arr_info;

	arr_info = gen_arr_info(ll);
	if (!arr_info)
		exit(1);
	*i = -1;
	return (arr_info);
}

int	*gen_arr_info(char **arr)
{
	int	i;
	int	size;
	int	*arr_info;

	size = arr_size(arr);
	arr_info = malloc(sizeof(int) * size);
	if (!arr_info)
		return (NULL);
	i = 0;
	while (i < size)
	{
		arr_info[i] = ft_strlen(arr[i]);
		i++;
	}
	return (arr_info);
}

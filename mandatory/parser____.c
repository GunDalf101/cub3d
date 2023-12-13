/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser____.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 03:33:35 by hbouhach          #+#    #+#             */
/*   Updated: 2023/12/09 12:21:38 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	token_count_in_str(char *str, char c)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}

int	read_map(t_map *map, int fd)
{
	char	*l;
	char	**lv;

	lv = ft_calloc(sizeof(char *), 2);
	if (!lv)
		return (1);
	l = non_empty_gnl(fd);
	if (!l)
		return (1);
	lv[0] = l;
	while (1)
	{
		l = get_next_line(fd);
		if (!l)
			break ;
		arr_push(&lv, strip_line(l));
	}
	map->map = lv;
	return (0);
}

int	read_texture(t_map *map, char *l, int *tfds)
{
	static int	seen[4];
	char		**splited;

	if (!l)
		return (1);
	splited = ft_split(l, ' ');
	if (!splited)
		return (1);
	if (verify_sprite(map, splited, seen, tfds))
		return (1);
	free_array(splited);
	return (0);
}

int	set_map_props(t_map *map)
{
	char	**lv;
	int		i;
	int		wmax;
	int		llen;

	lv = map->map;
	map->map_height = arr_size(lv);
	if (map->map_height < 3)
		return (1);
	wmax = 0;
	i = 0;
	while (i < map->map_height)
	{
		llen = ft_strlen(map->map[i]);
		if (llen > wmax)
			wmax = llen;
		i++;
	}
	map->map_width = wmax;
	return (pad_map(map));
}

int	read_rgbs(t_map *map, char *l)
{
	char		**splited;
	static int	seen[2];

	if (seen[0] && seen[1])
		return (1);
	splited = ft_split(l, ' ');
	if (arr_size(splited) != 2)
		return (free_array(splited), 1);
	else if (token_count_in_str(splited[1], ',') != 2)
		return (free_array(splited), 1);
	if (splited[0][0] == 'F')
	{
		if (fill_rgb(map->floor_rgb, splited[1]))
			return (free_array(splited), 1);
		seen[0] = 1;
	}
	else
	{
		if (fill_rgb(map->ceiling_rgb, splited[1]))
			return (free_array(splited), 1);
		seen[1] = 1;
	}
	free_array(splited);
	return (0);
}

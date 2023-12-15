/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_____.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 03:33:39 by hbouhach          #+#    #+#             */
/*   Updated: 2023/12/08 03:33:41 by hbouhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	verify_sprite(t_map *map, char **splited, int seen[4], int *tfds)
{
	int	i;

	if (arr_size(splited) != 2)
		return (1);
	if (ft_strlen(splited[0]) != 2)
		return (1);
	i = 0;
	while (i < 4)
	{
		if (!ft_strncmp(&("NOSOEAWE"[i * 2]), splited[0], 2) && !seen[i])
		{
			seen[i] = 1;
			break ;
		}
		i++;
	}
	if (i == 4)
		return (1);
	if (open_file(splited[1], tfds + i) < 0)
		return (1);
	else
		map->textures_paths[i] = ft_strdup(splited[1]);
	return (0);
}

int	fill_rgb(unsigned char rgb[3], char *rgbl)
{
	char	**splited;
	int		i;
	int		ret;

	(void)rgb;
	splited = ft_split(rgbl, ',');
	if (arr_size(splited) != 3)
		return (1);
	i = 0;
	while (i < 3)
	{
		if (is_all_digit(splited[i]))
			return (free_array(splited), 1);
		ret = ft_atoi(splited[i]);
		if (ret < 0 || ret > 255)
			return (free_array(splited), 1);
		rgb[i++] = ret;
	}
	free_array(splited);
	return (0);
}

int	check_token_counts(char **map_lines)
{
	static int	pdir_seen;
	int			i;
	int			j;
	char		*ret;

	i = -1;
	while (map_lines[++i])
	{
		j = -1;
		while (map_lines[i][++j])
		{
			if (map_lines[i][j] != ' ')
			{
				ret = ft_strchr(MAP_KNOWN_CHARS, map_lines[i][j]);
				if (EX_MAP_KNOWN_CHARS[((ret - MAP_KNOWN_CHARS) * 2)
						+ 1] == '!')
				{
					if (pdir_seen)
						perror_exit("duplicate unique-token in map.");
					pdir_seen = 1;
				}
			}
		}
	}
	return (!pdir_seen);
}

int	ends_with_ws(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] == '\t' || s[i] == ' ') && !s[i + 1])
			return (1);
		i++;
	}
	return (0);
}

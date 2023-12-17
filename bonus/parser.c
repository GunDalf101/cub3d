/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:12:37 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/13 00:40:18 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	run(char **maze, int *maze_info, int i, int j)
{
	if (!maze[i][j + 1] || !maze[i + 1] || i == 0 \
		|| j == 0 || maze_info[i + 1] <= j || maze_info[i - 1] <= j)
		return (1);
	if (maze[i][j + 1] == ' ')
		return (1);
	else if (maze[i][j - 1] == ' ')
		return (1);
	else if (maze[i - 1][j] == ' ')
		return (1);
	else if (maze[i + 1][j] == ' ')
		return (1);
	maze[i][j] = '1';
	if (ft_strchr(&MAP_KNOWN_CHARS[1], maze[i][j + 1]))
		run(maze, maze_info, i, j + 1);
	else if (ft_strchr(&MAP_KNOWN_CHARS[1], maze[i][j - 1]))
		run(maze, maze_info, i, j - 1);
	else if (maze_info[i] <= maze_info[i - 1] && ft_strchr(&MAP_KNOWN_CHARS[1],
			maze[i - 1][j]))
		run(maze, maze_info, i - 1, j);
	else if (maze_info[i] <= maze_info[i + 1] && ft_strchr(&MAP_KNOWN_CHARS[1],
			maze[i + 1][j]))
		run(maze, maze_info, i + 1, j);
	return (0);
}

static int	can_you_escape(char **ll)
{
	int	*arr_info;
	int	i;
	int	j;

	arr_info = init_stuff(ll, &i);
	while (ll[++i])
	{
		j = 0;
		while (ll[i][j])
		{
			if (!ft_strchr("1 ", ll[i][j]))
			{
				if (run(ll, arr_info, i, j))
					return (1337);
				else
				{
					i = -1;
					j = 0;
					break ;
				}
			}
			j++;
		}
	}
	return (free(arr_info), free_array(ll), 0);
}

static int	check_map(char **map_lines)
{
	int		i;
	int		j;
	char	**ll;

	i = -1;
	while (map_lines[++i])
	{
		if (!ft_strlen(map_lines[i]))
			return (perror_exit("empty line in map."), 1);
		j = 0;
		while (map_lines[i][j])
		{
			if (!start_walled(map_lines[i]) || !end_walled(map_lines[i]))
				return (perror_exit("unwalled line in map."), 1);
			if (map_lines[i][j] != ' ' && !ft_strchr(MAP_KNOWN_CHARS,
					map_lines[i][j]))
				return (perror_exit("unknown token in map."), 1);
			j++;
		}
	}
	ll = clone_arr(map_lines);
	if (!ll)
		perror_exit("System Error @ malloc().");
	return (this_or_that(check_token_counts(map_lines), can_you_escape(ll)));
}

static int	read_map_info(t_map *map, int fd, int *tfds)
{
	char	*l;
	int		inquired;

	inquired = 0;
	while (1)
	{
		l = non_empty_gnl(fd);
		if (!l || (ft_strlen(l) > 4 && l[3] == ' ') || ends_with_ws(l))
			return (free(l), perror_exit("Invalid map info."), 1);
		else if (str_starts_with(l, "NO ") || str_starts_with(l, "SO ")
			|| str_starts_with(l, "WE ") || str_starts_with(l, "EA "))
		{
			if (inquired++, read_texture(map, l, tfds))
				return (free(l), perror_exit("Invalid map info."), 1);
		}
		else if (str_starts_with(l, "F ") || str_starts_with(l, "C "))
		{
			if (inquired++, read_rgbs(map, l))
				return (free(l), perror_exit("Invalid map info."), 1);
		}
		else
			return (free(l), perror_exit("Invalid map info."), 1);
		if (free(l), inquired == 6)
			return (close_temp_fds(tfds));
	}
}

int	parser(char *filename, t_map *map)
{
	int	fd;
	int	tfds[4];
	int	ret;

	map->textures_paths = malloc(sizeof(char *) * 4);
	if (!map->textures_paths)
		perror_exit("System Error @ malloc().");
	if (check_filename_sanity(filename))
		return (1);
	if (open_file(filename, &fd) < 0)
		return (perror_exit("System Error @ open()."), 1);
	if (read_map_info(map, fd, tfds))
		return (1);
	if (read_map(map, fd))
		return (1);
	ret = check_map(map->map);
	if (ret == 1)
		perror_exit("missing mandatory token in map.");
	else if (ret == 1337)
		perror_exit("map is escapable.");
	if (!ensure_portals_sanity(map->map))
		return (perror_exit("Invalid portals."), 1);
	if (set_map_props(map))
		return (1);
	return (0);
}

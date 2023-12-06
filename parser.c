/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:12:37 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/06 23:12:38 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	check_filename_sanity(const char *filename)
{
	int	flen;

	flen = ft_strlen(filename);
	if (flen > 4 && filename[flen - 4] == '.' && filename[flen - 3] == 'c'
		&& filename[flen - 2] == 'u' && filename[flen - 1] == 'b')
		return (0);
	return (1);
}

static void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	open_file(char *filename, int *fd)
{
	*fd = open(filename, O_RDONLY);
	return (*fd);
}

static int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static char	*strip_line(char *l)
{
	int	len;

	len = ft_strlen(l);
	if (len)
	{
		if (l[len - 1] == '\n')
			l[len - 1] = '\0';
	}
	return (l);
}

static char	*non_empty_gnl(int fd)
{
	char	*l;

	while (1)
	{
		l = get_next_line(fd);
		if (!l)
			break ;
		if (l[0] == '\n' && l[1] == '\0')
		{
			free(l);
			continue ;
		}
		return (strip_line(l));
	}
	return (NULL);
}

static int	verify_sprite(t_map *map, char **splited, int seen[4], int *tfds)
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

static int	read_texture(t_map *map, char *l, int *tfds)
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

static int	is_all_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	fill_rgb(unsigned char rgb[3], char *rgbl)
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

static int	token_count_in_str(char *str, char c)
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

static int	read_rgbs(t_map *map, char *l)
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

static int	arr_push(char ***lv, char *nl)
{
	int		lv_size;
	int		i;
	char	**new_lv;

	lv_size = arr_size(*lv);
	new_lv = malloc(sizeof(char *) * (lv_size + 2));
	if (!new_lv)
		return (1);
	i = 0;
	while (i < lv_size)
	{
		new_lv[i] = (*lv)[i];
		i++;
	}
	new_lv[lv_size] = nl;
	new_lv[lv_size + 1] = NULL;
	free(*lv);
	*lv = new_lv;
	return (0);
}

static int	read_map(t_map *map, int fd)
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

static int	arr_has_any(int *arr, int len, int v)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (arr[i] == v)
			return (1);
		i++;
	}
	return (0);
}

static int	check_token_counts(char **map_lines)
{
	int		seen[10] = {0};
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (j = 0, map_lines[i])
	{
		while (map_lines[i][j])
		{
			if (map_lines[i][j] != ' ')
			{
				ret = ft_strchr(MAP_KNOWN_CHARS, map_lines[i][j]);
				if (EX_MAP_KNOWN_CHARS[((ret - MAP_KNOWN_CHARS) * 2)
					+ 1] == '!')
				{
					if (arr_has_any(seen, 10, 1))
						return (1);
					seen[ret - MAP_KNOWN_CHARS] = 1;
				}
			}
			j++;
		}
		i++;
	}
	return (!arr_has_any(seen, 10, 1));
}

static char	**clone_arr(char **arr)
{
	int		len;
	char	**copy;
	int		i;

	len = arr_size(arr);
	copy = malloc(sizeof(char *) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = ft_strdup(arr[i]);
		if (!copy[i])
			return (NULL);
		i++;
	}
	copy[len] = NULL;
	return (copy);
}

static int	run(char **maze, int *maze_info, int i, int j)
{
	if (!maze[i][j + 1] || !maze[i + 1] || i == 0 || j == 0)
		return (1);
	if (maze[i][j + 1] == ' ') // check right
		return (1);
	else if (maze[i][j - 1] == ' ') // check left
		return (1);
	else if (maze[i - 1][j] == ' ') // check up
		return (1);
	else if (maze[i + 1][j] == ' ') // check down
		return (1);
	maze[i][j] = '1';
	if (ft_strchr("0NSEW", maze[i][j + 1])) // look right
		run(maze, maze_info, i, j + 1);
	else if (ft_strchr("0NSEW", maze[i][j - 1])) // look left
		run(maze, maze_info, i, j - 1);
	else if (maze_info[i] <= maze_info[i - 1] && ft_strchr("0NSEW", maze[i
			- 1][j])) // look up
		run(maze, maze_info, i - 1, j);
	else if (maze_info[i] <= maze_info[i + 1] && ft_strchr("0NSEW", maze[i
			+ 1][j])) // look down
		run(maze, maze_info, i + 1, j);
	return (0);
}

static int	*gen_arr_info(char **arr)
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

static int	*init_stuff(char **ll, int *i)
{
	int	*arr_info;

	arr_info = gen_arr_info(ll);
	if (!arr_info)
		exit(1);
	*i = 0;
	return (arr_info);
}

static int	can_you_escape(char **ll)
{
	int	*arr_info;
	int	i;
	int	j;

	arr_info = init_stuff(ll, &i);
	while (j = 0, ll[i])
	{
		while (ll[i][j])
		{
			if (ll[i][j] == '0')
			{
				if (run(ll, arr_info, i, j))
					return (1);
				else
				{
					i = -1;
					j = 0;
					break ;
				}
			}
			j++;
		}
		i++;
	}
	return (free(arr_info), free_array(ll), 0);
}

static int	check_map(char **map_lines)
{
	int		i;
	int		j;
	char	**ll;

	i = 0;
	while (map_lines[i])
	{
		if (!ft_strlen(map_lines[i]))
			return (1);
		j = 0;
		while (map_lines[i][j])
		{
			if ((i == 0 || !map_lines[i + 1]) && !ft_strchr(" 1",
					map_lines[i][j]))
				return (1);
			if (map_lines[i][j] != ' ' && !ft_strchr(MAP_KNOWN_CHARS,
					map_lines[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	ll = clone_arr(map_lines);
	if (!ll)
		exit(1);
	return (check_token_counts(map_lines) || can_you_escape(ll));
}

static int	pad_map(t_map *map)
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

static int	set_map_props(t_map *map)
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

static int	str_starts_with(char *str, char *s)
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

static int	close_temp_fds(int tfds[4])
{
	int	i;

	i = 0;
	while (i < 4)
		close(tfds[i++]);
	return (0);
}

static int	read_map_info(t_map *map, int fd, int *tfds)
{
	char	*l;
	int		inquired;

	inquired = 0;
	while (1)
	{
		l = non_empty_gnl(fd);
		if (!l || (ft_strlen(l) > 4 && l[3] == ' '))
			return (1);
		else if (str_starts_with(l, "NO ") || str_starts_with(l, "SO ")
			|| str_starts_with(l, "WE ") || str_starts_with(l, "EA "))
		{
			if (inquired++, read_texture(map, l, tfds))
				return (free(l), 1);
		}
		else if (str_starts_with(l, "F ") || str_starts_with(l, "C "))
		{
			if (inquired++, read_rgbs(map, l))
				return (free(l), 1);
		}
		else
			return (free(l), 1);
		if (inquired == 6)
			return (free(l), close_temp_fds(tfds));
	}
}

int	parser(char *filename, t_map *map)
{
	int	fd;
	int	tfds[4];

	map->textures_paths = malloc(sizeof(char *) * 4);
	if (!map->textures_paths)
		return (1);
	if (check_filename_sanity(filename))
		return (1);
	printf("check_filename_sanity check.\n");
	if (open_file(filename, &fd) < 0)
		return (1);
	printf("open_file check.\n");
	if (read_map_info(map, fd, tfds))
		return (1);
	printf("read_map_info check.\n");
	if (read_map(map, fd))
		return (1);
	printf("read_map check.\n");
	if (check_map(map->map))
		return (1);
	printf("check_map check.\n");
	if (set_map_props(map))
		return (1);
	printf("set_map_props check.\n");
	return (0);
}

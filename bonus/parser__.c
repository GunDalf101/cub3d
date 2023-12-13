/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser__.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 03:33:25 by hbouhach          #+#    #+#             */
/*   Updated: 2023/12/08 03:33:27 by hbouhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_all_digit(char *str)
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

char	*non_empty_gnl(int fd)
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

int	arr_has_any(int *arr, int len, int v)
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

char	**clone_arr(char **arr)
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

int	arr_push(char ***lv, char *nl)
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

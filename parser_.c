/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 03:33:20 by hbouhach          #+#    #+#             */
/*   Updated: 2023/12/08 03:33:22 by hbouhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	check_filename_sanity(const char *filename)
{
	int	flen;

	flen = ft_strlen(filename);
	if (flen > 4 && filename[flen - 4] == '.' && filename[flen - 3] == 'c'
		&& filename[flen - 2] == 'u' && filename[flen - 1] == 'b')
		return (0);
	return (1);
}

void	free_array(char **arr)
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

int	open_file(char *filename, int *fd)
{
	*fd = open(filename, O_RDONLY);
	return (*fd);
}

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	*strip_line(char *l)
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

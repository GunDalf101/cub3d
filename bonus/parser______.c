/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser______.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:00:39 by hbouhach          #+#    #+#             */
/*   Updated: 2023/12/09 16:00:53 by hbouhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	start_walled(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	return (line[i] == '1');
}

int	end_walled(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (line[i] == ' ')
		i--;
	return (line[i] == '1');
}

void	perror_exit(char *str)
{
	printf("Error\n%s\n", str);
	exit(0);
}

int	this_or_that(int a, int b)
{
	if (a)
		return (a);
	return (b);
}

int	ensure_portals_sanity(char **map)
{
	int	i;
	int	j;
	int	yfound;
	int	zfound;

	i = 0;
	yfound = 0;
	zfound = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'Y')
				yfound++;
			else if (map[i][j] == 'Z')
				zfound++;
			j++;
		}
		i++;
	}
	return ((!yfound && !zfound) || \
			(yfound == 1 && zfound == 1));
}

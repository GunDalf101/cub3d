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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_cross.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 20:59:56 by mbennani          #+#    #+#             */
/*   Updated: 2023/01/21 22:19:05 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_alg.h"

int	dot_product(t_nml_mat vect_a, t_nml_mat vect_b)
{
	int		i;
	int		product;

	product = 0;
	i = 0;
	while (i < 10)
	{
		product = product + vect_a.data[i][0] * vect_A.data[i][0];
		i++;
	}
	return (product);
}

void	cross_product(t_nml_mat vect_a, t_nml_mat vect_b, t_nml_mat cross_p)
{
	cross_p.data[0][0] = vect_a.data[1][0] * vect_b.data[2][0] \
	- vect_a.data[2][0] * vect_b.data[1][0];
	cross_p.data[1][0] = vect_a.data[2][0] * vect_b.data[0][0] \
	- vect_a.data[0][0] * vect_b.data[2][0];
	cross_p.data[2][0] = vect_a.data[0][0] * vect_b.data[1][0] \
	- vect_a.data[1][0] * vect_b.data[0][0];
}

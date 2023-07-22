/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixV2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:14:54 by mbennani          #+#    #+#             */
/*   Updated: 2023/01/22 04:48:37 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_alg.h"

int	nml_mat_add_r(t_nml_mat *m1, t_nml_mat *m2)
{
	int	i;
	int	j;

	while (i < m1->num_rows)
	{
		while (j < m1->num_cols)
		{
			m1->data[i][j] += m2->data[i][j];
			j++;
		}
		i++;
	}
	return (1);
}

t_nml_mat	*nml_mat_add(t_nml_mat *m1, t_nml_mat *m2)
{
	t_nml_mat	*r;

	r = nml_mat_cp(m1);
	if (!nml_mat_add_r(r, m2))
	{
		nml_mat_free(r);
		return (NULL);
	}
	return (r);
}

t_nml_mat	*nml_mat_dot(t_nml_mat *m1, t_nml_mat *m2)
{
	int			i;
	int			j;
	int			k;
	t_nml_mat	*r;

	i = -1;
	r = nml_mat_new (m1->num_rows, m2->num_cols);
	if (!r)
		return (nml_mat_free(r), NULL);
	while (++i < r->num_rows)
	{
		j = -1;
		while (++j < r->num_cols)
		{
			k = -1;
			while (++k < m1->num_cols)
				r->data[i][j] += m1->data[i][k] * m2->data[k][j];
		}
	}
	return (r);
}

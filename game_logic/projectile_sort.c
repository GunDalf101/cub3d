/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:10:11 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/06 22:10:30 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

t_projectile	*merge(t_projectile *left, t_projectile *right)
{
	t_projectile	dummy;
	t_projectile	*tail;

	tail = &dummy;
	while (left && right)
	{
		if (left->proj_distance > right->proj_distance)
		{
			tail->next = left;
			left = left->next;
		}
		else
		{
			tail->next = right;
			right = right->next;
		}
		tail = tail->next;
	}
	if (left)
		tail->next = left;
	else
		tail->next = right;
	return (dummy.next);
}

t_projectile	*proj_sort(t_projectile *head)
{
	t_projectile	*slow;
	t_projectile	*fast;
	t_projectile	*right;
	t_projectile	*left_sorted;
	t_projectile	*right_sorted;

	if (head == NULL || head->next == NULL)
		return (head);
	slow = head;
	fast = head->next;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	right = slow->next;
	slow->next = NULL;
	left_sorted = proj_sort(head);
	right_sorted = proj_sort(right);
	return (merge(left_sorted, right_sorted));
}

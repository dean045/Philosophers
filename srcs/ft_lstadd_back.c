/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:11:49 by brhajji-          #+#    #+#             */
/*   Updated: 2022/06/01 14:53:28 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_lstadd_back(t_philo **alst, t_philo *new)
{
	t_philo	*tmp;

	tmp = (*alst);
	if (!tmp)
		tmp = new;
	else
	{
		while ((tmp)->next)
			tmp = (tmp)->next;
		(tmp)->next = new;
	}
}

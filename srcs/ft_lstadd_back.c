/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:11:49 by brhajji-          #+#    #+#             */
/*   Updated: 2022/05/23 08:35:12 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_lstadd_back(t_philo **alst, t_philo *new)
{
	if (!*alst)
		*alst = new;
	else
	{
		while ((*alst)->next)
			*alst = (*alst)->next;
		(*alst)->next = new;
	}
}

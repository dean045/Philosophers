/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:05:59 by brhajji-          #+#    #+#             */
/*   Updated: 2022/06/01 17:06:26 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_free(t_utils *utils)
{
	int		i;
	t_philo	*tmp;

	if (utils)
	{
		i = -1;
		while (++i < utils->nb_philo)
		{
			tmp = utils->philos->next;
			if (utils->philos)
				free(utils->philos);
			utils->philos = tmp;
		}
		if (utils->fchette)
			free(utils->fchette);
		free(utils);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:27:33 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/11 18:04:25 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	table()
{

}

int	main(int ac, char **av)
{
	pthread_mutex_t	*fchette;
	pthread_t		*philo;
	struct timeval	*tv;
	int				nb_philo;
	int				i;
	int				ret;

	if (ac == 5 || ac == 6)
	{
		i = 0;
		nb_philo = ft_atoi(av[1]);
		fchette = malloc(sizeof(pthread_mutex_t) * (nb_philo));
		philo = malloc(sizeof(pthread_t) * (nb_philo));
		while (i < philo)
		{
			ret = pthread_create (&philo[i], NULL, table, NULL);
			if (!ret)
			{
				
			}
		}
		
	}
	else
		printf("Invalid args");
}
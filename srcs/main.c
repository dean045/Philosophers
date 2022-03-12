/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:27:33 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/11 23:47:30 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat(t_utils *utils, t_philo *philo)
{
	usleep(utils->tteat.tv_usec * 1000);
}

void	s_sleep(t_utils *utils, t_philo *philo)
{
	usleep(utils->ttsleep.tv_usec  * 1000);
}

void	take_fork(t_philo *philo)
{

}

void	give_fork(t_philo *philo)
{

}

void	die(t_philo *philo)
{
	gettimeofday(&(philo->time), NULL);
	philo->status = 0;
}

static int table(t_utils *utils, t_philo *philo)
{
	int	x;
	struct timeval	tmp;

	x = utils->rot;
	gettimeofday(&(tmp), NULL);
	if (x < 0)
		x = 1;
	while (x)
	{
		if (utils->philos->time.tv_sec - tmp.tv_usec == utils->ttdie.tv_usec)
			die(philo);
		if (utils->rot)
			x--;
	}
}

void	init(t_utils *utils, char **av)
{
	int	i;
	t_philo	*tmp;

	i = -1;
	utils = malloc(sizeof(t_utils));
	utils->nb_philo = ft_atoi(av[1]);
	utils->philos = malloc(sizeof(t_philo));
	utils->fchette = malloc(sizeof(pthread_mutex_t) * (utils->nb_philo));
	while (++i < utils->nb_philo)
	{
		tmp = malloc(sizeof(t_philo));
		gettimeofday(&(tmp->time), NULL);
		tmp->next = utils->philos;
		if (!utils->philos)
		{
			utils->philos = tmp;
			utils->philos->next = NULL;
		}
	}
	
}

int	main(int ac, char **av)
{
	t_utils			*utils;
	struct timeval	*tv;
	int				i;
	int				ret;

	(void)(ac);
	(void)(av);
	init(utils, av);
	/*
	if (ac == 5 || ac == 6)
	{
		i = 0;
		while (i < utils->nb_philo)
		{
			/*ret = pthread_create (utils->philos->philo[i], NULL, table, utils);
			if (!ret)
			{
		}
	}
	else
		printf("Invalid args");
			}*/
}

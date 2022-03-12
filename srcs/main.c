/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:27:33 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/12 17:15:44 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat(t_utils *utils, t_philo *philo)
{
	struct timeval	tmp;

	gettimeofday(&(tmp), NULL);
	if (philo->status == 2)
	{
		printf("%06ld %i is eating\n", tmp.tv_usec, philo->num);
		usleep(utils->tteat.tv_usec * 1000);
	}
}

void	s_sleep(t_utils *utils, t_philo *philo)
{
	struct timeval	tmp;

	gettimeofday(&(tmp), NULL);
	printf("%06ld %i is sleeping\n", tmp.tv_usec, philo->num);
	usleep(utils->ttsleep.tv_usec  * 1000);
}

void	take_fork(t_philo *philo)
{
	struct timeval	tmp;

	gettimeofday(&(tmp), NULL);
	printf("%06ld %i  has taken a fork\n", tmp.tv_usec, philo->num);

}

void	give_fork(t_philo *philo)
{

}

void	die(t_philo *philo)
{
	gettimeofday(&(philo->time), NULL);
	philo->status = 0;
}

t_philo	*get_philo(t_utils *utils)
{
	int i;

	i = 0;
	while (i < utils->num_philo)
	{
		utils->philos = utils->philos->next;
		i++;	
	}
	return (utils->philos)
}

static int table(t_utils *utils)
{
	int	x;
	struct timeval	tmp;
	t_philo *philo;

	x = utils->rot;
	philo = get_philo(utils);
	gettimeofday(&(tmp), NULL);
	if (x < 0)
		x = 1;
	while (x)
	{
		if (tmp.tv_usec - utils->philos->time.tv_usec == utils->ttdie.tv_usec)
			die(philo);
		eat(utils, philo);
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
	utils->num_philo = 0;
	utils->philos = malloc(sizeof(t_philo));
	utils->fchette = malloc(sizeof(pthread_mutex_t) * (utils->nb_philo));
	while (++i < utils->nb_philo)
	{
		tmp = malloc(sizeof(t_philo));
		gettimeofday(&(tmp->time), NULL);
		tmp->num = i;
		tmp->next = utils->philos;
		if (!utils->philos)
		{
			utils->philos = tmp;
			utils->philos->next = NULL;
		}
	}
	ft_lstlast(utils->philos)->next = utils->philos;
}

int	main(int ac, char **av)
{
	t_utils			*utils;
	struct timeval	*tv;
	int				i;
	int				ret;


	init(utils, av);
	if (ac == 5 || ac == 6)
	{
		i = 0;
		while (i < utils->nb_philo)
		{
			utils->num_philo = i;
			ret = pthread_create (utils->philos->philo[i], NULL, table, utils);
			if (!ret)
			{
				  
			}
		}
	}
	else
		printf("Invalid args");
}

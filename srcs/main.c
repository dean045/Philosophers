/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:27:33 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/14 12:00:20 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*get_philo(t_utils *utils, int x)
{
	int i;

	i = 0;
	while (i < x)
	{
		utils->philos = utils->philos->next;
		i++;	
	}
	return (utils->philos);
}

void	eat(t_utils *utils, t_philo *philo)
{
	t_philo			*philo2;

	if (philo->status == 2)
	{
		pthread_mutex_lock(&(utils->fchette[philo->num]));
		philo2 = get_philo(utils, philo->num);
		philo2->right_hand = 0;
		philo->left_hand = 1;
		philo->status = 2;
		gettimeofday(&(utils->time), NULL);
		printf("%06d %i  has taken a fork\n", (utils->time.tv_usec / 1000), philo->num);
		printf("%06d %i is eating\n", (utils->time.tv_usec / 1000), philo->num);
		usleep(utils->tteat * 1000);
		gettimeofday(&(philo->time), NULL);
		philo2->right_hand = 1;
		philo->left_hand = 0;
		philo->status = 1;
		pthread_mutex_unlock(&(utils->fchette[philo->num]));
	}

}

void	s_sleep(t_utils *utils, t_philo *philo)
{
	struct timeval	tmp;

	gettimeofday(&(tmp), NULL);
	printf("%06d %i is sleeping\n", (tmp.tv_usec / 1000), philo->num);
	usleep(utils->ttsleep  * 1000);
}

void	die(t_philo *philo)
{
	gettimeofday(&(philo->time), NULL);
	philo->status = 0;
}

void *table(void *param)
{
	int	x;
	struct timeval	tmp;
	t_philo *philo;
	t_utils	*utils;

	//printf("test\n");
	utils = (t_utils *)param;
	x = utils->rot;
	philo = NULL;
	philo = get_philo(utils, utils->num_philo);
	gettimeofday(&(tmp), NULL);
	if (x < 0)
		x = 1;
	while (x)
	{
		eat(utils, philo);
		if (utils->rot)
			x--;
		if (tmp.tv_usec - utils->philos->time.tv_usec == utils->ttdie)
			die(philo);
	}
	return (NULL);
}

void	init(t_utils **utils, char **av)
{
	int	i;
	t_philo	*tmp;

	i = -1;
	(*utils) = calloc(sizeof(t_utils), 1);
	(*utils)->nb_philo = ft_atoi(av[1]);
	(*utils)->ttdie = ft_atoi(av[2]);
	(*utils)->tteat = ft_atoi(av[3]);
	(*utils)->ttsleep = ft_atoi(av[4]);
	(*utils)->rot = ft_atoi(av[5]);
	(*utils)->num_philo = 0;
	//utils->philos = malloc(sizeof(t_philo));
	(*utils)->philos = NULL;
	(*utils)->fchette = malloc(sizeof(pthread_mutex_t) * ((*utils)->nb_philo));
	while (++i < (*utils)->nb_philo)
	{
		tmp = malloc(sizeof(t_philo));
		gettimeofday(&(tmp->time), NULL);
		tmp->num = i;
		tmp->right_hand = 1;
		tmp->left_hand = 0;
		tmp->next = (*utils)->philos;
		(*utils)->philos = tmp;
	}
	i = -1;
	while (++i < (*utils)->nb_philo)
		pthread_mutex_init(&((*utils)->fchette[i]), NULL);
	ft_lstlast((*utils)->philos)->next = (*utils)->philos;
}

int	main(int ac, char **av)
{
	t_utils			*utils;
	int				i;
	int				ret;


	if (ac == 5 || ac == 6)
	{
		utils = NULL;
		init(&utils, av);
		i = -1;
		while (++i < utils->nb_philo)
		{
			utils->num_philo = i;
			ret = pthread_create (&(utils->philos->philo), NULL, table, (void *)utils);
			/*if (!ret)
			{
				  
			}*/
		}
	}
	else
		printf("Invalid args");
}

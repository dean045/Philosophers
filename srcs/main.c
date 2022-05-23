/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:27:33 by brhajji-          #+#    #+#             */
/*   Updated: 2022/05/23 14:01:43 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*init_philo(t_utils *utils, int i, int av5)
{
	t_philo	*tmp;

	tmp = malloc(sizeof(t_philo));
	if (!tmp)
		return (NULL);
	tmp->num = i;
	tmp->rot = av5;
	tmp->next = utils->philos;
	return (tmp);
}

void	init(t_utils **utils, char **av, int ac)
{
	int	i;
	int	rot;
	
	rot = -1;
	if (ac == 6)
		rot = ft_atoi(av[5]);
	i = -1;
	(*utils) = calloc(sizeof(t_utils), 1);
	if (!utils)
		return ;
	(*utils)->nb_philo = ft_atoi(av[1]);
	(*utils)->rot_done = 0;
	(*utils)->ttdie = ft_atoi(av[2]);
	(*utils)->tteat = ft_atoi(av[3]);
	(*utils)->ttsleep = ft_atoi(av[4]);
	pthread_mutex_init(&((*utils)->death), NULL);
	pthread_mutex_init(&((*utils)->mute_rot), NULL);
	(*utils)->philos = NULL;
	(*utils)->gameover = 0;
	(*utils)->fchette = malloc(sizeof(pthread_mutex_t) * ((*utils)->nb_philo));
	if (!(*utils)->fchette)
		return ;
	while (++i < (*utils)->nb_philo)
	{
		(*utils)->philos = init_philo(*utils, i, rot);
		pthread_mutex_init(&((*utils)->fchette[i]), NULL);
	}
	ft_lstlast((*utils)->philos)->next = (*utils)->philos;
}

int	main(int ac, char **av)
{
	t_utils			*utils;
	int				i;
	int				ret;

	(void) ret;
	if (ac == 5 || ac == 6)
	{
		utils = NULL;
		init(&utils, av, ac);
		i = 0;
		gettimeofday(&((utils)->start), NULL);
		while (++i <= utils->nb_philo && utils->philos)
		{
			if (i % 2 == 1)
			{
				pthread_mutex_init(&((utils)->philos->block), NULL);
				pthread_mutex_lock(&(utils->philos->block));
				gettimeofday(&(utils->philos->time), NULL);
				//printf("before philo num = %i , time = %li\n",utils->philos->num+1, convert(utils->philos->time));
				pthread_mutex_unlock(&(utils->philos->block));
				ret = pthread_create (&(utils->philos->philo), NULL, table, (void *)utils);
				utils->philos = utils->philos->next;
				usleep(5);
			}
		}
		i = 0;
		while (++i <= utils->nb_philo && utils->philos)
		{
			if (i % 2 == 0)
			{
				pthread_mutex_init(&((utils)->philos->block), NULL);
				pthread_mutex_lock(&(utils->philos->block));
				gettimeofday(&(utils->philos->time), NULL);
				//printf("before philo num = %i , time = %li\n",utils->philos->num+1, convert(utils->philos->time));
				pthread_mutex_unlock(&(utils->philos->block));
				ret = pthread_create (&(utils->philos->philo), NULL, table, (void *)utils);
				utils->philos = utils->philos->next;
				usleep(5);
			}
		}
		i = -1;
		while (get_gameover(utils) == 0 && get_rot(utils) == 0)
			check_death(utils);
		while (++i < utils->nb_philo)
		{
			pthread_join((utils->philos->philo), NULL);
			utils->philos = utils->philos->next;
		}
	}
	else
		printf("Invalid args");
}

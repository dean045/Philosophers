/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 00:16:25 by brhajji-          #+#    #+#             */
/*   Updated: 2022/05/22 05:52:28 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat(t_utils *utils, t_philo *philo)
{
	t_philo			*philo2;

	philo2 = philo->next;

	//printf("test %i\n", utils->gameover);
	pthread_mutex_lock(&(utils->fchette[philo->num]));
	///printf("%ld %i has taken a fork\n", maj(utils->start), philo->num+1);
	pthread_mutex_lock(&(utils->fchette[philo2->num]));
	//printf("%ld %i has taken a fork\n", maj(utils->start), philo->num+1);
	printf("%ld %i is eating\n", maj(utils->start), philo->num+1);
	s_sleep(utils, utils->tteat);
	philo->rot = philo->rot - 1;
	pthread_mutex_unlock(&(utils->fchette[philo2->num]));
	pthread_mutex_unlock(&(utils->fchette[philo->num]));
	pthread_mutex_lock(&(philo->block));
	gettimeofday(&(philo->time), NULL);
	pthread_mutex_unlock(&(philo->block));
}

void	eat_last(t_utils *utils, t_philo *philo)
{
	t_philo			*philo2;

	philo2 = philo->next;

	pthread_mutex_lock(&(utils->fchette[philo2->num]));
	//printf("%ld %i has taken a fork\n", maj(utils->start), philo->num+1);
	pthread_mutex_lock(&(utils->fchette[philo->num]));
	//printf("%ld %i has taken a fork\n", maj(utils->start), philo->num+1);
	printf("%ld %i is eating\n", maj(utils->start), philo->num+1);
	s_sleep(utils, utils->tteat);
	philo->rot--;
	pthread_mutex_unlock(&(utils->fchette[philo->num]));
	pthread_mutex_unlock(&(utils->fchette[philo2->num]));
	pthread_mutex_lock(&(philo->block));
	gettimeofday(&(philo->time), NULL);
	pthread_mutex_unlock(&(philo->block));
}



void *table(void *param)
{
	t_philo 		*philo;
	t_utils			*utils;

	utils = (t_utils *)param;
	philo = NULL;
	//printf("table i = %i\n", utils->num_philo+1);
	philo = get_philo(utils, utils->num_philo);
	while (philo->rot != 0 && get_gameover(utils) == 0)
	{
		if (philo->num == utils->nb_philo - 1)
			eat_last(utils, philo);
		else
			eat(utils, philo);
		printf("%ld %i is sleeping\n", maj(utils->start), philo->num+1);
		s_sleep(utils, utils->ttsleep);
		if (get_gameover(utils)  == 0)
			print(philo->num, 1, maj(utils->start));
	}
	pthread_mutex_lock(&(utils->death));
	utils->gameover = 1;
	pthread_mutex_unlock(&(utils->death));
	return (NULL);
}

void ft_usleep(int time)
{
	int	i;

	i = -1;
	while (++i < (time * 5))
		usleep(200);
}
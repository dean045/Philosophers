/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 00:16:25 by brhajji-          #+#    #+#             */
/*   Updated: 2022/05/23 13:59:04 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat(t_utils *utils, t_philo *philo)
{
	pthread_mutex_lock(&(utils->fchette[philo->num + 1]));
	print(utils, philo->num, 2, maj(utils->start));
	pthread_mutex_lock(&(utils->fchette[philo->num]));
	print(utils, philo->num, 2, maj(utils->start));
	print(utils, philo->num, 3, maj(utils->start));
	pthread_mutex_lock(&(philo->block));
	gettimeofday(&(philo->time), NULL);
	pthread_mutex_unlock(&(philo->block));
	s_sleep(utils, utils->tteat);
	philo->rot = philo->rot - 1;
	pthread_mutex_unlock(&(utils->fchette[philo->num]));
	pthread_mutex_unlock(&(utils->fchette[philo->num + 1]));
}

void	eat_last(t_utils *utils, t_philo *philo)
{
	pthread_mutex_lock(&(utils->fchette[philo->num]));
	print(utils, philo->num, 2, maj(utils->start));
	pthread_mutex_lock(&(utils->fchette[0]));
	print(utils, philo->num, 2, maj(utils->start));
	print(utils, philo->num, 3, maj(utils->start));
	pthread_mutex_lock(&(philo->block));
	gettimeofday(&(philo->time), NULL);
	pthread_mutex_unlock(&(philo->block));
	s_sleep(utils, utils->tteat);
	philo->rot--;
	pthread_mutex_unlock(&(utils->fchette[0]));
	pthread_mutex_unlock(&(utils->fchette[philo->num]));
}


void *table(void *param)
{
	t_philo 		*philo;
	t_utils			*utils;

	utils = (t_utils *)param;
	philo = (utils->philos);
	while (philo->rot != 0 && get_gameover(utils) == 0)
	{
		if (philo->num == utils->nb_philo - 1)
			eat_last(utils, philo);
		else
			eat(utils, philo);
		if (philo->rot != 0)
		{
			print(utils, philo->num, 4, maj(utils->start));
			s_sleep(utils, utils->ttsleep);
		}
		else
		{
			pthread_mutex_lock(&(utils->mute_rot));
			utils->rot_done++;
			pthread_mutex_unlock(&(utils->mute_rot));
		}
		if (get_gameover(utils) == 0 && philo->rot != 0)
			print(utils, philo->num, 1, maj(utils->start));
	}
	return (NULL);
}

int	check_death(t_utils *utils)
{
	int				i;
	int				ret;
	struct timeval	current;


	i = -1;
	ret = -1;
	while (++i < utils->nb_philo && ret == -1)
	{
		pthread_mutex_lock(&(utils->death));
		pthread_mutex_lock(&(utils->philos->block));
		gettimeofday(&(current), NULL);
		if (convert(utils->philos->time) + utils->ttdie <= convert(current))
		{
			ret = (utils->philos->num);
			utils->gameover = 1;
		}
		pthread_mutex_unlock(&(utils->philos->block));
		pthread_mutex_unlock(&(utils->death));
		utils->philos = utils->philos->next;
		//usleep(20);
	}
	if (ret != -1)
		print(utils, ret, 0, maj(utils->start));
	return (ret);
}
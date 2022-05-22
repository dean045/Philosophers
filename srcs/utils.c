/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:10:17 by brhajji-          #+#    #+#             */
/*   Updated: 2022/05/22 17:11:28 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*get_philo(t_utils *utils, int x)
{
	while (utils->philos->num != x)
		utils->philos = utils->philos->next;
	return (utils->philos);
}

void	print(t_utils *utils, int philo, int etat, long int time)
{
	if (etat == 0)
	{
		printf("%li %i is dead\n", time, philo +1);
		exit(0);
	}
	else if (get_gameover(utils) == 0)
	{
		if (etat == 1)
			printf("%ld %i is thinking\n", time, philo+1);
		else if (etat == 2)
			printf("%ld %i has taken a fork\n", time, philo+1);
		else if (etat == 3)
			printf("%ld %i is eating\n", time, philo+1);
		else if (etat == 4)
			printf("%ld %i is sleeping\n", time, philo+1);
	}
}

long int	maj(struct timeval start)
{
	struct timeval	tmp;
	
	gettimeofday(&(tmp), NULL);
	return (convert(tmp) - convert(start));
}

void	s_sleep(t_utils *utils, int time)
{
	int	i;

	i = -1;
	while (get_gameover(utils) == 0 && ((++i) < time / 8))
	{
		usleep(8000);
	}
}

long int	convert(struct timeval tmp)
{
	return ((tmp.tv_sec * 1000) + (tmp.tv_usec / 1000));
}

int get_gameover(t_utils *utils)
{
	int	x;

	x = 0;
	pthread_mutex_lock(&(utils->death));
	if (utils->gameover == 1)
		x = 1;
	pthread_mutex_unlock(&(utils->death));
	return	(x);
}

int get_rot(t_utils *utils)
{
	int	x;

	x = 0;
	pthread_mutex_lock(&(utils->mute_rot));
	if (utils->rot_done == utils->nb_philo)
		x = 1;
	pthread_mutex_unlock(&(utils->mute_rot));
	return	(x);
}
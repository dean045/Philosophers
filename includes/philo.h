/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:28:06 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/11 23:36:46 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_philo
{
	pthread_t		*philo;
	struct s_philo	*next;
	int				status;
	struct timeval	time;
}	t_philo;

typedef struct s_utils
{
	pthread_mutex_t	*fchette;
	struct s_philo	*philos;
	int				nb_philo;
	struct timeval	tteat;
	struct timeval	ttdie;
	struct timeval	ttsleep;
	int				rot;
}	t_utils;

int	ft_atoi(const char *str);

#endif
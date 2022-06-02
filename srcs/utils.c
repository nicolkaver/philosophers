/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:46:09 by nboratko          #+#    #+#             */
/*   Updated: 2022/06/01 14:34:30 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* Je print chaque action de mes philos
 * caller = 0 si philo, 1 si checker */

void	print_action(t_data *data, t_philo *philo, char *str, int caller)
{
	if (!caller)
		pthread_mutex_lock(&(data->exit));
	if (!data->stop)
	{
		pthread_mutex_lock(&(data->writing));
		printf("\e[34m%ld\e[0m ", get_timestamp(data));
		printf("%d ", philo->index + 1);
		printf("%s\n", str);
		pthread_mutex_unlock(&(data->writing));
	}
	if (!caller)
		pthread_mutex_unlock(&data->exit);
}

void	stop_simulation(t_data *data)
{
	pthread_mutex_lock(&data->exit);
	data->stop = 1;
	pthread_mutex_unlock(&data->exit);
}

int	check_stop(t_data *data)
{
	pthread_mutex_lock(&(data->exit));
	if (data->stop)
	{
		pthread_mutex_unlock(&data->exit);
		return (1);
	}
	pthread_mutex_unlock(&data->exit);
	return (0);
}

/* struct timeval est le premier argument de la fonction gettimeofday
 * elle comprend tv_sec (seconds) et tv_usec (microsecondes)
 * il faut donc les multiplier par 1000 dans le premier cas et les 
 * diviser par 1000 dans le deuxieme afin d'obtenir notre valeur 
 * en microscondes comme demande dans le sujet */

long	get_timestamp(t_data *data)
{
	long	time_sec;
	long	time_msec;

	gettimeofday(&data->time, NULL);
	time_sec = data->time.tv_sec - data->start.tv_sec;
	time_msec = data->time.tv_usec / 1000 - data->start.tv_usec / 1000;
	if (time_msec < 0)
	{
		time_msec += 1000;
		time_sec -= 1;
	}
	time_sec = (time_sec * 1000) + time_msec;
	return (time_sec);
}

void	call_me_when_you_die(t_data *data, t_philo **philo, int i)
{
	pthread_mutex_lock(&data->exit);
	print_action(data, *philo, "died 💀😭", 1);
	data->stop = 1;
	pthread_mutex_unlock(&data->exit);
	pthread_mutex_unlock(&(*philo)[i].check_meal);
}

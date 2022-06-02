/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:47:36 by nboratko          #+#    #+#             */
/*   Updated: 2022/05/23 19:59:35 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* Les philos doivent etre indexes a partir de 1 */

void	init_philos(t_data *data, t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		(*philo)[i].data = data;
		(*philo)[i].index = i;
		(*philo)[i].all_ate = 0;
		(*philo)[i].last_ate = 0;
		(*philo)[i].count_eat = 0;
	}
}

int	init_mutex(t_data *data, t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (1);
		if (pthread_mutex_init(&(*philo)[i].check_meal, NULL))
			return (1);
	}
	if (pthread_mutex_init(&(data->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(data->exit), NULL))
		return (1);
	return (0);
}

int	init_data(t_data *data, char **av)
{
	data->n_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (data->n_philo == -1 || data->t_die == -1 || data->t_eat == -1
		||data->t_sleep == -1)
		return (error_msg("Invalid argument value detected\n"));
	if (data->n_philo <= 0 || data->t_die < 0
		|| data->t_eat < 0 || data->t_sleep < 0)
		return (error_msg("Invalid argument value detected\n"));
	if (av[5])
	{
		data->n_eat = ft_atoi(av[5]);
		if (data->n_eat <= 0)
			return (error_msg("Invalid argument value detected\n"));
	}
	else
		data->n_eat = -1;
	data->stop = 0;
	return (0);
}

int	init_all(t_data *data, t_philo **philo)
{
	*philo = malloc(sizeof(t_philo) * data->n_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!*philo || !data->forks)
		return (1);
	if (init_mutex(data, philo))
		return (1);
	init_philos(data, philo);
	return (0);
}

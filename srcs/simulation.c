/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:22:03 by nboratko          #+#    #+#             */
/*   Updated: 2022/06/01 15:54:56 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eating(t_philo *philo)
{
	if (philo->data->n_philo == 1)
	{
		fork_mutex(1, philo, 0);
		ft_usleep(philo->data, philo->data->t_die + 10000);
		fork_mutex(0, philo, 0);
		return ;
	}
	fork_action(philo, 1);
	pthread_mutex_lock(&(philo->check_meal));
	philo->last_ate = get_timestamp(philo->data);
	pthread_mutex_unlock(&(philo->check_meal));
	print_action(philo->data, philo, "is eating 🍝", 0);
	ft_usleep(philo->data, philo->data->t_eat);
	(philo->count_eat)++;
	if (philo->count_eat == philo->data->n_eat && philo->all_ate != 1)
	{
		pthread_mutex_lock(&(philo->check_meal));
		philo->all_ate = 1;
		pthread_mutex_unlock(&(philo->check_meal));
	}
	fork_action(philo, 0);
}

void	*thread_func(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	while (!check_stop(philo->data) && philo->all_ate != 1)
	{
		if (!check_stop(philo->data))
			eating(philo);
		print_action(philo->data, philo, "is sleeping 😴", 0);
		ft_usleep(philo->data, philo->data->t_sleep);
		print_action(philo->data, philo, "is thinking 🤔", 0);
	}
	return (0);
}

int	end_checker(t_data *data, t_philo **philo)
{
	int	i;
	int	finish;

	i = -1;
	finish = 1;
	while (++i < data->n_philo)
	{
		pthread_mutex_lock(&(*philo)[i].check_meal);
		if ((*philo)[i].all_ate == 0)
			finish = 0;
		pthread_mutex_unlock(&(*philo)[i].check_meal);
		pthread_mutex_lock(&(*philo)[i].check_meal);
		if (get_timestamp(data) - (*philo)[i].last_ate >= data->t_die)
		{
			call_me_when_you_die(data, philo, i);
			return (1);
		}
		pthread_mutex_unlock(&(*philo)[i].check_meal);
	}
	if (finish == 1)
		return (1);
	return (0);
}

void	end(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_join((*philo)[i].phil_thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		pthread_mutex_destroy(&(*philo)[i].check_meal);
		i++;
	}
	pthread_mutex_destroy(&(data->writing));
	pthread_mutex_destroy(&(data->exit));
	ft_free((void **)philo);
	ft_free((void **)&(data->forks));
}

/* Si death_checker est positif (tout le monde a mange n_eat fois
 * ou un philo est mort, on appelle alors la fonction stop_simulation
 * qui mettra data->stop a 1. Ceci aura pour but de sortir de la fonction
 * thread_func et la simulation sera terminee. */

void	start(t_data *data, t_philo **philo)
{
	int	i;

	gettimeofday(&data->start, NULL);
	i = -1;
	while (++i < data->n_philo)
	{
		if (i % 2 != 0)
			usleep(1000);
		if (pthread_create(&(*philo)[i].phil_thread, NULL, \
			&thread_func, (void *)&(*philo)[i]))
		{
			printf("Failed to create the thread\n");
			break ;
		}
	}
	while (1)
	{
		usleep(1000);
		if (end_checker(data, philo))
		{
			stop_simulation(data);
			break ;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:27:47 by nboratko          #+#    #+#             */
/*   Updated: 2022/06/01 12:12:51 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	fork_mutex(int lock, t_philo *philo, int fork_i)
{
	if (lock)
	{
		pthread_mutex_lock(&(philo->data->forks[fork_i]));
		print_action(philo->data, philo, "has taken a fork 🍽️", 0);
	}
	else
		pthread_mutex_unlock(&(philo->data->forks[fork_i]));
}

/* On lock ou unlock la premiere fourchette dont l'index est le meme que 
 * celui du philo. On verifie ensuite s'il s'agit du dernier philo. 
 * Si oui, l'index de la deuxieme fourchette est 0.
 * Si oui, l'index est i+1 */

/* Pour eviter le data race, les philos impairs vont d'abord prendre
 * la fourchette gauche (i), puis droite (i+1) et les pairs l'inverse */

void	fork_action(t_philo *philo, int action)
{
	int	i;

	i = philo->index;
	if (i % 2 != 0)
	{	
		fork_mutex(action, philo, i);
		if (i != philo->data->n_philo - 1)
			fork_mutex(action, philo, i + 1);
		else
			fork_mutex(action, philo, 0);
	}
	else
	{
		if (i != philo->data->n_philo -1)
			fork_mutex(action, philo, i + 1);
		else
			fork_mutex(action, philo, 0);
		fork_mutex(action, philo, i);
	}
}

/* On s'assure dans cette fonction que notre argument (t_eat, t_something)
 * a ete respecte. On va verifier toutes les 50 microsecondes qu'aucun 
 * philo n'est mort et qu'il ne faut pas arreter la simulation */

void	ft_usleep(t_data *data, int t_something)
{
	long	i;

	i = get_timestamp(data);
	while (!check_stop(data)
		&& (get_timestamp(data) - i) < t_something)
		usleep(50);
}

void	ft_free(void **something)
{
	free(*something);
	*something = NULL;
}

int	error_msg(char *s)
{
	printf("%s", s);
	return (1);
}

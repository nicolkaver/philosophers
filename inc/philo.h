/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 20:32:06 by nboratko          #+#    #+#             */
/*   Updated: 2022/06/01 14:34:08 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define MAX_INT 2147483647

// print emoji https://emojidb.org/printf-emojis

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	int				index;
	int				count_eat;
	long			last_ate;
	int				all_ate;
	pthread_mutex_t	check_meal;
	pthread_t		phil_thread;
}	t_philo;

typedef struct s_data
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				stop;
	struct timeval	time;
	struct timeval	start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing;
	pthread_mutex_t	exit;
}		t_data;

//INITS
int		init_data(t_data *data, char **av);
void	init_philos(t_data *data, t_philo **philos);
int		init_mutex(t_data *data, t_philo **philo);
int		init_all(t_data *data, t_philo **philo);

//MAIN
int		check_args(char **av);
int		main(int argc, char **argv);

//SIMULATION
void	eating(t_philo *philo);
void	*thread_func(void *void_philo);
int		end_checker(t_data *data, t_philo **philo);
void	end(t_data *data, t_philo **philo);
void	start(t_data *data, t_philo **philo);

//LIBFT_UTILS
int		ft_isdigit(int c);
int		ft_atoi(char *s);

//UTILS
void	print_action(t_data *data, t_philo *philo, char *str, int caller);
long	get_timestamp(t_data *data);
void	ft_usleep(t_data *data, int t_something);
int		check_stop(t_data *data);
void	call_me_when_you_die(t_data *data, t_philo **philo, int i);

//UTILS2
void	fork_mutex(int lock, t_philo *philo, int fork_i);
void	fork_action(t_philo *philo, int action);
void	ft_free(void **something);
int		error_msg(char *s);
void	stop_simulation(t_data *data);

#endif

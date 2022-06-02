/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 21:17:36 by nboratko          #+#    #+#             */
/*   Updated: 2022/06/02 12:42:18 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{	
			if (av[i][j] == '-')
			{
				printf("Enter positive values only\n");
				return (1);
			}
			if (!ft_isdigit(av[i][j]))
			{
				printf("All arguments must be numbers\n");
				return (1);
			}
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
	{
		printf("Error : Wrong number of arguments\n");
		return (EXIT_FAILURE);
	}
	if (check_args(argv))
		return (EXIT_FAILURE);
	if (init_data(&data, argv))
		return (EXIT_FAILURE);
	if (!init_all(&data, &philo))
	{
		start(&data, &philo);
		end(&data, &philo);
	}
	return (EXIT_SUCCESS);
}

/* Pour les tests:
./philo 1 800 200 200 : 1 philosophe doit mourir
./philo 5 800 200 200 : aucun philosophe ne doit mourir
./philo 5 800 200 200 7 : aucun ne moeurt et chacun mange 7 fois
./philo 4 410 200 200 : aucun philo ne doit mourir
./philo 4 310 200 100 : 1 philo doit mourir */

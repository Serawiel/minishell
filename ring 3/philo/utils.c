/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:17:03 by cprot             #+#    #+#             */
/*   Updated: 2025/10/03 11:17:05 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	int		s;
	int		i;
	long	nb;

	nb = 0;
	s = 1;
	i = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			s = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	nb = nb * s;
	if (nb > INT_MAX || nb < INT_MIN)
		return (0);
	return ((int)nb);
}

int	ft_is_digit(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

void	cleanup_simulation(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->args.nbr_philo)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		pthread_mutex_destroy(&sim->philos[i].philo_mutex);
		i++;
	}
	pthread_mutex_destroy(&sim->print_mutex);
	pthread_mutex_destroy(&sim->death_mutex);
	free(sim->philos);
	free(sim->forks);
}

int	init_philos(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->args.nbr_philo)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].times_eat = 0;
		sim->philos[i].time_last_meal = 0;
		sim->philos[i].sim = sim;
		sim->philos[i].left_fork = &sim->forks[i];
		sim->philos[i].right_fork = &sim->forks[(i + 1) % sim->args.nbr_philo];
		pthread_mutex_init(&sim->philos[i].philo_mutex, NULL);
		i++;
	}
	return (1);
}

int	init_simulation(t_simulation *sim, t_args args)
{
	int	i;

	i = 0;
	sim->args = args;
	sim->philos = malloc(sizeof(t_philo) * args.nbr_philo);
	sim->forks = malloc(sizeof(pthread_mutex_t) * args.nbr_philo);
	sim->start_time = get_time_ms();
	if (!sim->philos || !sim->forks)
		return (0);
	while (i < args.nbr_philo)
	{
		pthread_mutex_init(&sim->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&sim->print_mutex, NULL);
	pthread_mutex_init(&sim->death_mutex, NULL);
	sim->someone_died = 0;
	return (1);
}

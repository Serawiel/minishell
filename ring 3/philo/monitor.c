/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:20:24 by cprot             #+#    #+#             */
/*   Updated: 2025/10/03 11:20:25 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_simulation *sim)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&sim->death_mutex);
	result = sim->someone_died;
	pthread_mutex_unlock(&sim->death_mutex);
	return (result);
}

int	check_philosopher_death(t_simulation *sim, int i)
{
	long long	current;
	long long	last_meal;

	current = get_timestamp(sim);
	pthread_mutex_lock(&sim->philos[i].philo_mutex);
	last_meal = sim->philos[i].time_last_meal;
	pthread_mutex_unlock(&sim->philos[i].philo_mutex);
	if ((current - last_meal) >= sim->args.time_to_die)
	{
		pthread_mutex_lock(&sim->death_mutex);
		sim->someone_died = 1;
		pthread_mutex_unlock(&sim->death_mutex);
		pthread_mutex_lock(&sim->print_mutex);
		printf("%lld %d died\n", current, sim->philos[i].id);
		pthread_mutex_unlock(&sim->print_mutex);
		return (1);
	}
	return (0);
}

int	monitor_times_eat(t_simulation *sim)
{
	int	i;

	if (sim->args.nbr_times_must == -1)
		return (0);
	i = 0;
	while (i < sim->args.nbr_philo)
	{
		pthread_mutex_lock(&sim->philos[i].philo_mutex);
		if (sim->philos[i].times_eat >= sim->args.nbr_times_must)
		{
			pthread_mutex_unlock(&sim->philos[i].philo_mutex);
			i++;
		}
		else
		{
			pthread_mutex_unlock(&sim->philos[i].philo_mutex);
			return (0);
		}
	}
	return (1);
}

void	*monitor_death(void *arg)
{
	t_simulation	*sim;
	int				i;

	sim = (t_simulation *)arg;
	while (!check_death(sim))
	{
		i = 0;
		while (i < sim->args.nbr_philo)
		{
			if (check_philosopher_death(sim, i))
				return (NULL);
			i++;
		}
		if (monitor_times_eat(sim))
		{
			pthread_mutex_lock(&sim->death_mutex);
			sim->someone_died = 1;
			pthread_mutex_unlock(&sim->death_mutex);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:17:28 by cprot             #+#    #+#             */
/*   Updated: 2025/10/03 11:17:29 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_fork_normal(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (check_death(philo->sim))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	print_status(philo->sim, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	if (check_death(philo->sim))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	print_status(philo->sim, philo->id, "has taken a fork");
	return (1);
}

int	take_fork_reverse(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (check_death(philo->sim))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	print_status(philo->sim, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	if (check_death(philo->sim))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	print_status(philo->sim, philo->id, "has taken a fork");
	return (1);
}

void	eat(t_philo *philo)
{
	if (check_death(philo->sim))
		return ;
	if (philo->id % 2 == 0)
	{
		if (!take_fork_reverse(philo))
			return ;
	}
	else
	{
		if (!take_fork_normal(philo))
			return ;
	}
	pthread_mutex_lock(&philo->philo_mutex);
	philo->times_eat++;
	philo->time_last_meal = get_timestamp(philo->sim);
	pthread_mutex_unlock(&philo->philo_mutex);
	print_status(philo->sim, philo->id, "is eating");
	ft_usleep(philo->sim->args.time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (philo->sim->args.nbr_philo % 2 == 1)
		usleep(5000);
}

void	philo_cycle(t_philo *philo)
{
	eat(philo);
	if (check_death(philo->sim))
		return ;
	print_status(philo->sim, philo->id, "is sleeping");
	ft_usleep(philo->sim->args.time_to_sleep);
	if (check_death(philo->sim))
		return ;
	print_status(philo->sim, philo->id, "is thinking");
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->sim->args.nbr_philo == 1)
	{
		print_status(philo->sim, philo->id, "has taken a fork");
		ft_usleep(philo->sim->args.time_to_die + 1);
		return (NULL);
	}
	pthread_mutex_lock(&philo->philo_mutex);
	philo->time_last_meal = get_timestamp(philo->sim);
	pthread_mutex_unlock(&philo->philo_mutex);
	if (philo->id % 2 == 0)
		usleep(100);
	while (!check_death(philo->sim))
		philo_cycle(philo);
	return (NULL);
}

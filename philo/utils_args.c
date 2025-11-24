/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:17:11 by cprot             #+#    #+#             */
/*   Updated: 2025/10/03 11:17:13 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!ft_is_digit(av[i]))
			return (0);
		i++;
	}
	return (1);
}

int	validate_args(t_args args)
{
	if (args.nbr_philo <= 0)
		return (0);
	if (args.time_to_die < 0)
		return (0);
	if (args.time_to_eat < 0)
		return (0);
	if (args.time_to_sleep < 0)
		return (0);
	return (1);
}

t_args	create_args(char **av)
{
	t_args	args;

	args.nbr_philo = ft_atoi(av[1]);
	args.time_to_die = ft_atoi(av[2]);
	args.time_to_eat = ft_atoi(av[3]);
	args.time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		args.nbr_times_must = ft_atoi(av[5]);
	else
		args.nbr_times_must = -1;
	return (args);
}

void	print_status(t_simulation *sim, int philo_id, char *status)
{
	pthread_mutex_lock(&sim->print_mutex);
	if (!check_death(sim))
		printf("%lld %d %s\n", get_timestamp(sim), philo_id, status);
	pthread_mutex_unlock(&sim->print_mutex);
}

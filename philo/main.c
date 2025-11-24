/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:20:32 by cprot             #+#    #+#             */
/*   Updated: 2025/10/03 11:22:46 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_simulation(t_simulation *sim)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	pthread_create(&monitor_thread, NULL, monitor_death, sim);
	while (i < sim->args.nbr_philo)
	{
		pthread_create(&sim->philos[i].thread_id, NULL, philosopher_routine,
			&sim->philos[i]);
		i++;
	}
	i = 0;
	while (i < sim->args.nbr_philo)
	{
		pthread_join(sim->philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	usleep(1000);
	return (1);
}

int	main(int ac, char **av)
{
	t_args			args;
	t_simulation	sim;

	if (ac < 5 || ac > 6)
		return (write(2,
				"Usage: ./philo nb_philo time_die time_eat time_sleep "
				"[nb_meals]\n",
				64));
	if (!check_args(av))
		return (write(2, "Error: Invalid arguments\n", 25));
	args = create_args(av);
	if (!validate_args(args))
		return (write(2, "Error: Arguments out of range\n", 30));
	if (!init_simulation(&sim, args))
		return (write(2, "Error: init_simulation failed\n", 30));
	if (!init_philos(&sim))
		return (write(2, "Error: init_philos failed\n", 26));
	start_simulation(&sim);
	usleep(1000);
	cleanup_simulation(&sim);
	return (0);
}

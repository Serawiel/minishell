/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:17:21 by cprot             #+#    #+#             */
/*   Updated: 2025/10/03 11:17:22 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time_ms(void)
{
	long long		time_in_ms;
	struct timeval	time_val;

	gettimeofday(&time_val, NULL);
	time_in_ms = (time_val.tv_sec * 1000) + (time_val.tv_usec / 1000);
	return (time_in_ms);
}

long long	get_timestamp(t_simulation *sim)
{
	return (get_time_ms() - sim->start_time);
}

void	ft_usleep(long long time_ms)
{
	long long	current;
	long long	start;

	current = 0;
	start = get_time_ms();
	while ((current - start) < time_ms)
	{
		current = get_time_ms();
		usleep(100);
	}
	return ;
}

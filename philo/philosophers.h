/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:17:41 by cprot             #+#    #+#             */
/*   Updated: 2025/10/03 11:17:42 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>  // toutes les fonctions pthread_*
# include <stdio.h>    // printf
# include <stdlib.h>   // malloc, free
# include <string.h>   // memset
# include <sys/time.h> // gettimeofday
# include <unistd.h>   // write, usleep

// define
typedef struct s_simulation	t_simulation;
typedef struct s_philo		t_philo;

// struct
typedef struct s_args
{
	int						nbr_philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						nbr_times_must;
}							t_args;

typedef struct s_simulation
{
	t_args					args;
	t_philo					*philos;
	long long				start_time;
	pthread_mutex_t			*forks;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			death_mutex;
	int						someone_died;
}							t_simulation;

typedef struct s_philo
{
	int						id;
	int						times_eat;
	long long				time_last_meal;
	pthread_t				thread_id;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			philo_mutex;
	t_simulation			*sim;
}							t_philo;

// UTILS
int							ft_atoi(const char *nptr);
int							ft_is_digit(char *str);
void						cleanup_simulation(t_simulation *sim);
int							init_philos(t_simulation *sim);
int							init_simulation(t_simulation *sim, t_args args);

// UTILS_ARGS
int							validate_args(t_args args);
t_args						create_args(char **av);
int							check_args(char **av);
void						print_status(t_simulation *sim, int philo_id,
								char *status);

// ROUTINE
void						*philosopher_routine(void *arg);

// MONITOR
int							check_death(t_simulation *sim);
void						*monitor_death(void *arg);

// TIME
long long					get_time_ms(void);
long long					get_timestamp(t_simulation *sim);
void						ft_usleep(long long time_ms);

#endif
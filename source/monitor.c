/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:32:19 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/17 11:31:32 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleep_monitor(long long duration, t_program *program)
{
	long long	start;
	long long	current;
	int			dead;

	start = get_current_time();
	current = start;
	dead = 0;
	while (current - start < duration)
	{
		pthread_mutex_lock(&program->death_mutex);
		dead = program->death_flag;
		pthread_mutex_unlock(&program->death_mutex);
		if (dead)
			break ;
		usleep(10);
		current = get_current_time();
	}
}

int	start_monitor(t_program *program)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, monitor_routine, program) != 0)
	{
		printf("Error: failed to create monitor thread.\n");
		return (1);
	}
	pthread_detach(monitor_thread);
	return (0);
}

int	check_philo_death(t_philo *philo, t_program *program)
{
	long long	current_time;
	long long	temp_start_time;
	int			died;

	pthread_mutex_lock(&philo->meal_mutex);
	current_time = get_current_time();
	died = (current_time - philo->meal_last > program->time_to_die);
	pthread_mutex_unlock(&philo->meal_mutex);
	if (died)
	{
		pthread_mutex_lock(&program->print_mutex);
		temp_start_time = program->start_time;
		printf("[%lld ms] Philosopher %d died\n",
			current_time - temp_start_time,
			philo->philo_id);
		pthread_mutex_unlock(&program->print_mutex);
		pthread_mutex_lock(&program->death_mutex);
		program->death_flag = 1;
		pthread_mutex_unlock(&program->death_mutex);
	}
	return (died);
}

void	*monitor_routine(void *arg)
{
	t_program	*program;
	int			i;

	program = (t_program *)arg;
	while (should_continue(program))
	{
		i = 0;
		while (i < program->philo_count)
		{
			if (program->times_to_eat != -1 && program->philos[i].meal_count >= program->times_to_eat)
			{
				i++;
				continue ;
			}
			if (check_philo_death(&program->philos[i], program))
				return (NULL);
			i++;
		}
		usleep(10);
	}
	return (NULL);
}
















// other


// void *monitor_routine(void *arg)
// {
// 	printf("2\n");
// 	t_program *program = (t_program *)arg;
// 	int	i;
// 	long long current_time;

// 	while (program->death_flag == 0)
// 	{
// 		i = 0;
// 		while (i < program->philo_count)
// 		{
// 			t_philo *philo = &program->philos[i];
// 			// Skip philosophers that already finished their meals
// 			if (program->times_to_eat != -1 && philo->meal_count >= program->times_to_eat)
// 			{
// 				i++;
// 				continue ;
// 			}
// 			current_time = get_current_time();
// 			if (current_time - philo->meal_last > program->time_to_die)
// 			{
// 				pthread_mutex_lock(&program->print_mutex);
// 				printf("[%lld ms] Philosopher %d died\n",
// 					current_time - program->start_time,
// 					philo->philo_id);
// 				pthread_mutex_unlock(&program->print_mutex);
// 				program->death_flag = 1;
// 				return NULL;
// 			}
// 			i++;
// 		}
// 		usleep(10);
// 	}
// 	return (NULL);
// }
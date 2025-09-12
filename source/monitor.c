/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:32:19 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/12 15:29:13 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
			Simulation starts
			┌─────────────┐
			│ Main thread │
			└───┬─────────┘
				│
				│ Create philosopher threads (think/eat/sleep)
				│
				│ Create monitor thread
				▼
			┌────────────────┐
			│ Monitor thread │
			└───┬────────────┘
				│
				├─ continuously checks each philosopher:
				│     current_time - meal_last > time_to_die?
				│
				├─ If YES:
				│     print death
				│     death_flag = 1
				│     exit monitor
				│
				└─ If NO:
						wait 1ms → repeat

*/
#include "philosophers.h"

void	sleep_monitor(long long duration, t_program *program)
{
	long long	start = get_current_time();
	while (get_current_time() - start < duration)
	{
		if (program->death_flag)
			break ;
		usleep(1000);
	}
}

int	start_monitor(t_program *program)
{
	pthread_t monitor_thread;

	if (pthread_create(&monitor_thread, NULL, monitor_routine, program) != 0)
	{
		printf("Error: failed to create monitor thread.\n");
		return 1;
	}
	pthread_detach(monitor_thread);
	return (0);
}

void *monitor_routine(void *arg)
{
	t_program *program = (t_program *)arg;
	int i;

	while (program->death_flag == 0)
	{
		i = 0;
		while (i < program->philo_count)
		{
			t_philo *philo = &program->philos[i];

			// Skip philosophers that already finished their meals
			if (program->times_to_eat != -1 && philo->meal_count >= program->times_to_eat)
			{
				i++;
				continue;
			}
			long long current_time = get_current_time();
			if (current_time - philo->meal_last > program->time_to_die)
			{
				pthread_mutex_lock(&program->print_mutex);
				printf("[%lld ms] Philosopher %d died\n",
					current_time - program->start_time,
					philo->philo_id);
				pthread_mutex_unlock(&program->print_mutex);
				program->death_flag = 1;
				return NULL;
			}
			i++;
		}
		// Reduce CPU usage
		usleep(1000); // 1ms
	}
	return (NULL);
}



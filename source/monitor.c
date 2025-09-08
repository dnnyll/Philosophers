/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:32:19 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/08 14:44:41 by daniefe2         ###   ########.fr       */
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

// void	print_message(char *str, t_philo *philo, int id)
// {
// 	size_t	time;

// 	pthread_mutex_lock(philo->write_lock);
// 	time = get_current_time() - philo->start_time;
// 	if (!dead_loop(philo))
// 		printf("%zu %d %s\n", time, id, str);
// 	pthread_mutex_unlock(philo->write_lock);
// }
int start_monitor(t_program *program)
{
	pthread_t monitor_thread;

	// Create a separate thread for the monitor routine
	if (pthread_create(&monitor_thread, NULL, monitor_routine, program) != 0)
	{
		printf("Error: failed to create monitor thread.\n");
		return 1;
	}

	// We don't need to join the monitor because we want it to run independently
	pthread_detach(monitor_thread);
	return 0;
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
			long long current_time = get_current_time();
			// Check if this philosopher has exceeded time_to_die
			if (current_time - program->philos[i].meal_last > program->time_to_die)
			{
				pthread_mutex_lock(&program->print_mutex);
				printf("[%lld ms] Philosopher %d died\n",
					current_time - program->start_time,
					program->philos[i].philo_id);
				pthread_mutex_unlock(&program->print_mutex);
				program->death_flag = 1;
				return NULL; // stop monitor
			}
			i++;
		}
		// Reduce CPU usage
		usleep(1000); // 1ms
	}
	return NULL;
}



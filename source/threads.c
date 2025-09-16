/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:17:49 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/16 14:15:28 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/*
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);

Arguments explained:

pthread_t *thread
	Pointer to a pthread_t variable where the thread ID of the new thread will be stored.
	This ID can later be used to manage the thread (e.g., join it).

const pthread_attr_t *attr
	Pointer to a structure that specifies thread attributes (stack size, detached state, scheduling, etc.).
	If NULL, default attributes are used.

void *(*start_routine)(void *)
	Function pointer to the function the thread will execute.
	The function must take a single void * argument and return a void *.

void *arg
	Pointer to an argument passed to the start_routine function.
	Can be NULL if no argument is needed.
*/
// void	thread_clean(t_program *program)
// {
// 	int	i;

// 	i = 0;
// 	while (i < program->philo_count)
// 	{
// 		pthread_mutex_destroy(&program->forks[i]);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&program->print_mutex);
// 	free(program->forks);
// 	free(program->philos);
// }

int	thread_create(t_program *program, t_philo *philo)
{
	int i = 0;
	// int	j = 1;

	while (i < program->philo_count)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]) != 0)
		{
			while (i > 0)
			{
				thread_join(program, philo);
				i--;
			}
			printf("Error creating thread for philosopher %d\n", philo[i].philo_id);
			return (1);
		}
		// printf("thread_create %d\n", j++);
		i++;
	}
	return (0);
}

int	thread_join(t_program *program, t_philo *philo)
{
	int	i;
	
	i = 0;
	while (i < program->philo_count)
	{
		// printf("Joining philosopher %d's thread...\n", philo[i].philo_id);
		if (pthread_join(philo[i].thread, NULL) != 0)
		{
			printf("Error joining thread for philosopher %d\n", philo[i].philo_id);
			return 1;
		}
		// printf("Philosopher %d's thread has finished.\n", philo[i].philo_id);
		i++;
	}
	return (0);
}

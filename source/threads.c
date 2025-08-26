/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:17:49 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/26 15:40:38 by daniefe2         ###   ########.fr       */
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
int	thread_create(t_program *program, t_philo *philo)
{
	int	i;
	
	i = 0;
	while (i < program->philo_count)
	{
		pthread_create(philo->thread, NULL, philo_routine, &philo);
		i++;
	}
}
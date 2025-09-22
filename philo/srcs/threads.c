/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:17:49 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/18 17:05:55 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	thread_create(t_program *program, t_philo *philo)
{
	int	i;
	int	j;

	i = 0;
	while (i < program->philo_count)
	{
		if (pthread_create(&philo[i].thread, NULL,
				philo_routine, &philo[i]) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_join(philo[j].thread, NULL);
				j++;
			}
			return (1);
		}
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
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	create_philosopher_threads(t_program *program, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < program->philo_count)
	{
		if (pthread_create(&philo[i].thread, NULL,
				philo_routine, &philo[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(philo[i].thread, NULL);
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_monitor_thread(t_program *program, pthread_t *monitor_thread)
{
	if (program->philo_count <= 1)
		return (0);
	if (pthread_create(monitor_thread, NULL, monitor_routine, program) != 0)
		return (1);
	return (0);
}

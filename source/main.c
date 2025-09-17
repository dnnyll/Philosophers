/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:12:56 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/17 10:05:40 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// int		static process input

static int	init_start(t_program *program, t_philo *philo)
{
	int	i;
	
	pthread_mutex_lock(&philo->meal_mutex);
	program->start_time = get_current_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	i = 0;
	while (i < program->philo_count)
	{
		pthread_mutex_lock(&program->philos[i].meal_mutex);
		program->philos[i].meal_last = program->start_time;
		pthread_mutex_unlock(&program->philos[i].meal_mutex);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_program	program;
	t_philo		*philo;

	if (argc < 5 || argc > 6)
	{
		printf("Error: incorrect number of input arguments.\n");
		return (1);
	}
	if (verify_input_args(argv) == 1)
	{
		printf("Error: invalid input.\n");
		return (1);
	}
	philo = init_all(&program, argv);
	if (!philo)
		return (1);
	if (thread_create(&program, philo) != 0)
	{
		printf("Error: thread creation failed.\n");
		return (1);
	}
	init_start(&program, philo);
	if (program.philo_count > 1)
		start_monitor(&program);
	thread_join(&program, philo);
	cleanup(&program);
	free_all(&program);
	return (0);
}


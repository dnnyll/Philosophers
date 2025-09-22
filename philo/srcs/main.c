/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:12:56 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/22 11:39:14 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_input(int argc, char **argv)
{
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
	return (0);
}

int	main(int argc, char **argv)
{
	t_program	program;
	t_philo		*philo;
	pthread_t	monitor_thread;
	int			monitor_created;

	if (check_input(argc, argv) != 0)
		return (1);
	philo = init_all(&program, argv);
	if (!philo)
		return (1);
	monitor_created = 0;
	if (create_philosopher_threads(&program, philo) != 0)
		return (1);
	if (program.philo_count > 1
		&& create_monitor_thread(&program, &monitor_thread) == 0)
		monitor_created = 1;
	thread_join(&program, philo);
	if (monitor_created)
		pthread_join(monitor_thread, NULL);
	cleanup(&program);
	return (0);
}

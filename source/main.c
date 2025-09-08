/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:12:56 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/08 15:15:00 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
		main() starts
			|
		validate input
			|
		initialize program & philosophers
			|
		thread_create -> starts all philosopher threads
			|
		philosopher threads run in parallel (thinking/eating/sleeping)
			|
		thread_join -> main waits for all threads to finish
			|
		cleanup -> free memory, destroy mutexes
*/


#include "philosophers.h"

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

	
	// 2. Start monitor thread (checks death_flag, meal limits)
	if (start_monitor(&program) != 0)
	{
		printf("Error: monitor thread failed.\n");
		return (1);
	}
	
	// 1. Start all philosopher threads
	if (thread_create(&program, philo) != 0)
	{
		printf("Error: thread creation failed.\n");
		return (1);
	}
	// 3. Join philosopher threads when done
	if (thread_join(&program, philo) != 0)
	{
		printf("Error: thread join failed.\n");
		return (1);
	}

	// 4. Cleanup mutexes, free memory
	// cleanup(&program, philo);

	return (0);
}


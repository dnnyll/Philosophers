/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:13:29 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/22 09:25:20 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_input(t_program *program, char **argv)
{
	program->philo_count = ft_atoi(argv[1]);
	program->time_to_die = ft_atoi(argv[2]);
	program->time_to_eat = ft_atoi(argv[3]);
	program->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		program->times_to_eat = ft_atoi(argv[5]);
	else
		program->times_to_eat = -1;
	return (0);
}
//	assignment of values for left and right forks from allocated mutex array
//	% number of philosophers allows last philo right fork to be 1st philo left fork
int	init_philo(t_philo *philo, t_program *program)
{
	int	i;

	i = 0;
	while (i < program->philo_count)
	{
		philo[i].philo_id = i + 1;
		philo[i].meal_count = 0;
		philo[i].meal_last = program->start_time;
		philo[i].program = program;
		philo[i].left_fork = &program->forks[i];
		philo[i].right_fork = &program->forks[(i + 1) % program->philo_count];
		pthread_mutex_init(&philo[i].meal_mutex, NULL);
		i++;
	}
	return (0);
}
//	allocation of an array of mutex based on the number of threads/philosophers
int	init_program(t_program *program)
{
	int	i;

	program->death_flag = 0;
	program->start_time = get_current_time();
	program->threads_ready = 0;
	program->meals_end = 0;
	program->forks = malloc(sizeof(pthread_mutex_t) * program->philo_count);
	if (!program->forks)
		return (1);
	pthread_mutex_init(&program->death_mutex, NULL);
	pthread_mutex_init(&program->print_mutex, NULL);
	pthread_mutex_init(&program->meals_mutex, NULL);
	i = 0;
	while (i < program->philo_count)
	{
		pthread_mutex_init(&program->forks[i], NULL);
		i++;
	}
	return (0);
}

t_philo	*allocate_philos(int count)
{
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * count);
	if (!philos)
		return (NULL);
	return (philos);
}

t_philo	*init_all(t_program *program, char **argv)
{
	t_philo	*philos;

	if (init_input(program, argv) != 0)
		return (NULL);
	if (init_program(program) != 0)
		return (NULL);
	philos = malloc(sizeof(t_philo) * program->philo_count);
	if (!philos)
	{
		free(program->forks);
		return (NULL);
	}
	if (init_philo(philos, program) != 0)
	{
		free(philos);
		free(program->forks);
		return (NULL);
	}
	program->philos = philos;
	return (philos);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 09:40:41 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/22 11:21:06 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	clear_forks(t_program *program)
{
	int	i;

	if (program->forks)
	{
		i = 0;
		while (i < program->philo_count)
		{
			pthread_mutex_destroy(&program->forks[i]);
			i++;
		}
		free(program->forks);
		program->forks = NULL;
	}
}

static void	destroy_all_mutex(t_program *program)
{
	pthread_mutex_destroy(&program->meals_mutex);
	pthread_mutex_destroy(&program->print_mutex);
	pthread_mutex_destroy(&program->death_mutex);
}

static void	clear_philos(t_program *program)
{
	int	i;

	if (program->philos)
	{
		i = 0;
		while (i < program->philo_count)
		{
			pthread_mutex_destroy(&program->philos[i].meal_mutex);
			i++;
		}
		free(program->philos);
		program->philos = NULL;
	}
}

static void	free_and_reset(t_program *program)
{
	if (program->forks)
	{
		free(program->forks);
		program->forks = NULL;
	}
	if (program->philos)
	{
		free(program->philos);
		program->philos = NULL;
	}
}

void	cleanup(t_program *program)
{
	if (!program)
		return ;
	clear_forks(program);
	destroy_all_mutex(program);
	clear_philos(program);
	free_and_reset(program);
}

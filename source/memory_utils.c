/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 09:40:41 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/17 11:31:38 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup(t_program *program)
{
	int	i;

	if (!program)
		return ;
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
	pthread_mutex_destroy(&program->print_mutex);
	// pthread_mutex_destroy(&program->death_mutex);
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

void	free_all(t_program *program)
{
	if (!program)
		return ;
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

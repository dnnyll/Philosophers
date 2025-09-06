/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 09:40:41 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/06 09:49:43 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_program(t_program *program)
{
	int	i;

	if (!program)
		return;
	if (program->forks)
	{
		i = 0;
		while (i < program->philo_count)
		{
			pthread_mutex_destroy(&program->forks[i]);
			i++;
		}
		free(program->forks);
	}
	pthread_mutex_destroy(&program->print_mutex);
}

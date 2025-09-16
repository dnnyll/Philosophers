/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:49:23 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/16 16:50:34 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(t_philo *philo, const char *action)
{
	t_program	*program;
	int			dead;

	program = philo->program;

	pthread_mutex_lock(&program->death_mutex);
	dead = program->death_flag;
	pthread_mutex_unlock(&program->death_mutex);
	if (!dead)
	{
		pthread_mutex_lock(&program->print_mutex);
		printf("%lld Philosopher %d %s\n",
			get_current_time() - program->start_time,
			philo->philo_id,
			action);
		pthread_mutex_unlock(&program->print_mutex);
	}
}
// void print_action(t_philo *philo, const char *action)
// {
// 	t_program *program;

// 	program = philo->program;
// 	pthread_mutex_lock(&program->print_mutex);
// 	if (!program->death_flag)
// 		printf("%lld Philosopher %d %s\n",
// 			get_current_time() - program->start_time,
// 			philo->philo_id,
// 			action);
// 	pthread_mutex_unlock(&program->print_mutex);
// }
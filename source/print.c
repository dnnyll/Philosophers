/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:49:23 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/17 16:23:06 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	print_action(t_philo *philo, const char *action)
{
	t_program	*program;

	program = philo->program;
	pthread_mutex_lock(&program->print_mutex);
	pthread_mutex_lock(&program->death_mutex);
	if (program->death_flag == 0)
	{
		if (action[0] == 'd')
			program->death_flag = 1;
		printf("%lld Philosopher %d %s\n",
			get_current_time() - program->start_time,
			philo->philo_id,
			action);
	}
	pthread_mutex_unlock(&program->death_mutex);
	pthread_mutex_unlock(&program->print_mutex);
}

// void	print_action(t_philo *philo, const char *action)
// {
// 	t_program	*program;
// 	static int			dead = 0;

	
// 	// pthread_mutex_lock(&program->death_mutex);
// 	// dead = program->death_flag;
// 	// pthread_mutex_unlock(&program->death_mutex);
// 	program = philo->program;
// 	pthread_mutex_lock(&program->print_mutex);
// 	if (dead == 0)
// 	{
// 		if (action[0] == 'd')
// 		{
// 			dead = 1;
// 			pthread_mutex_lock(&program->death_mutex);
// 			program->death_flag = 1;
// 			pthread_mutex_unlock(&program->death_mutex);
// 		}
// 		printf("%lld Philosopher %d %s\n",
// 			get_current_time() - program->start_time,
// 			philo->philo_id,
// 			action);
// 	}
// 	pthread_mutex_unlock(&program->print_mutex);
// }
// void	print_action(t_philo *philo, const char *action)
// {
// 	t_program	*program;
// 	int			dead;

// 	program = philo->program;

// 	pthread_mutex_lock(&program->death_mutex);
// 	dead = program->death_flag;
// 	pthread_mutex_unlock(&program->death_mutex);
// 	if (!dead)
// 	{
// 		pthread_mutex_lock(&program->print_mutex);
// 		printf("%lld Philosopher %d %s\n",
// 			get_current_time() - program->start_time,
// 			philo->philo_id,
// 			action);
// 		pthread_mutex_unlock(&program->print_mutex);
// 	}
// }
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:37:45 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/15 16:48:01 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void print_action(t_philo *philo, const char *action)
{
	t_program *program = philo->program;

	// if (program->death_flag)
	// 	return ;

	pthread_mutex_lock(&program->print_mutex); 	// Lock the print mutex to avoid overlapping prints
	if (!program->death_flag)
		printf("%lld Philosopher %d %s\n",
			get_current_time() - program->start_time,
			philo->philo_id,
			action);
	pthread_mutex_unlock(&program->print_mutex);
}

void take_forks(t_philo *philo)
{
	// if(philo->program->philo_count == 1)
	// {
	// 	pthread_mutex_lock(philo->left_fork);
	// 	print_action(philo, "has taken a fork");
	// 	// usleep(philo->program->time_to_die * 1000);
	// 	pthread_mutex_unlock(philo->left_fork);
	// 	return ;
	// }
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
}

void	release_forks(t_philo *philo)
{
	// if(philo->program->philo_count == 1)
	// {
	// 	pthread_mutex_unlock(philo->left_fork);
	// 	return ;
	// }
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	to_think(t_philo *philo)
{
	t_program *program;
	
	program = philo->program;
	// if (program->death_flag)
	// 	return ;
	pthread_mutex_lock(&program->print_mutex);
	if (!program->death_flag)
		printf("%lld Philosopher %d is thinking\n",
			get_current_time() - program->start_time,
			philo->philo_id);
	pthread_mutex_unlock(&program->print_mutex);
	sleep_monitor(10, program);
}

void	to_eat(t_philo *philo)
{
	t_program *program;

	program = philo->program;
	// if (program->death_flag)
	// return ;
	take_forks(philo);
	
	philo->meal_last = get_current_time();
	philo->meal_count++;
	print_action(philo, "is eating");
	sleep_monitor(program->time_to_eat, program);
	release_forks(philo);
}

void	to_sleep(t_philo *philo)
{
	t_program *program;

	program = philo->program;
	if (program->death_flag)
		return ;
	print_action(philo, "is sleeping");
	sleep_monitor(program->time_to_sleep, program);
}

void	*philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_program *program = philo->program;
	
	if (philo->philo_id % 2 == 0)
		usleep(20);
	while (!program->death_flag &&
		(program->times_to_eat == -1 || philo->meal_count < program->times_to_eat))
	{
		to_eat(philo);
		to_sleep(philo);
		to_think(philo);
		// if (program->death_flag)
		// 	break ;
	}
	return (NULL);
}

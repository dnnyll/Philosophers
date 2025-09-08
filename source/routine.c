/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:37:45 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/08 14:38:48 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void to_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->print_mutex);
	printf("%lld Philosopher %d is thinking\n",
		get_current_time() - philo->program->start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->program->print_mutex);
}

void	to_eat(t_philo *philo)
{
	t_program *program = philo->program;

	// 1. Take forks (mutex lock)
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}

	// 2. Eat
	philo->meal_last = get_current_time();
	philo->meal_count++;

	// 3. Print eating
	pthread_mutex_lock(&program->print_mutex);
	printf("%lld Philosopher %d is eating (meal %d)\n",
		philo->meal_last - program->start_time, philo->philo_id, philo->meal_count);
	pthread_mutex_unlock(&program->print_mutex);
	
	usleep(program->time_to_eat * 1000);

	// 4. Release forks
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	to_sleep(t_philo *philo)
{
	t_program *program = philo->program;

	pthread_mutex_lock(&program->print_mutex);
	printf("%lld Philosopher %d is sleeping\n",
		get_current_time() - program->start_time, philo->philo_id);
	pthread_mutex_unlock(&program->print_mutex);

	usleep(program->time_to_sleep * 1000);
}

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_program *program = philo->program;

	while (program->death_flag == 0 &&
			(program->times_to_eat == -1 || philo->meal_count < program->times_to_eat))
	{
		if(program->death_flag)
			break ;
		to_think(philo);   // 1. Think
		if(program->death_flag)
			break ;
		to_eat(philo);  // 2. Take forks + eat + release forks
		if(program->death_flag)
			break ;
		to_sleep(philo); // 3. Sleep
		// if(program->death_flag)
		// 	break ;
	}
	return (NULL);
}

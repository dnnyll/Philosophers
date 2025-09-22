/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:51:08 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/18 17:02:16 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	grab_forks(t_philo *philo)
{
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
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	to_think(t_philo *philo)
{
	t_program	*program;

	program = philo->program;
	pthread_mutex_lock(&program->print_mutex);
	if (check_death_flag(program))
		printf("%lld Philosopher %d is thinking\n",
			get_current_time() - program->start_time,
			philo->philo_id);
	pthread_mutex_unlock(&program->print_mutex);
	sleep_monitor(5, program);
}

void	to_eat(t_philo	*philo)
{
	t_program	*program;

	program = philo->program;
	grab_forks(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meal_last = get_current_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_action(philo, "is eating");
	sleep_monitor(program->time_to_eat, program);
	release_forks(philo);
}

void	to_sleep(t_philo *philo)
{
	t_program	*program;

	program = philo->program;
	print_action(philo, "is sleeping");
	sleep_monitor(program->time_to_sleep, program);
}

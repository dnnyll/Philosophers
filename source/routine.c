/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:37:45 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/17 09:52:18 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	should_continue(t_program *program)
{
	int	flag;

	pthread_mutex_lock(&program->death_mutex);
	flag = !program->death_flag;
	pthread_mutex_unlock(&program->death_mutex);
	return (flag);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	t_program	*program;
	int			temp_meal_count;
	
	philo = (t_philo *)arg;
	program = philo->program;
	pthread_mutex_lock(&philo->meal_mutex);
	temp_meal_count = philo->meal_count;
	pthread_mutex_unlock(&philo->meal_mutex);
	if(program->philo_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_unlock(philo->left_fork);
		sleep_monitor(program->time_to_die, program);
		printf("[%lld ms] Philosopher %d died\n",
					program->time_to_die,
					philo->philo_id);
		return (NULL);
	}
	if (philo->philo_id % 2 == 0)
		usleep(20);
	while (should_continue(program) &&
		(program->times_to_eat == -1 || temp_meal_count < program->times_to_eat))
	{
		if(!should_continue(program))
			break;
		to_eat(philo);
		if(!should_continue(program))
			break;
		// fork_left = 0
		to_sleep(philo);
		if(!should_continue(program))
			break;
		to_think(philo);
		if(!should_continue(program))
			break;
	}
	return (NULL);
}

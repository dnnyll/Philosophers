/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:37:45 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/06 11:01:31 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
void	odd_or_even()
{
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

*/

// void	to_sleep(t_philo *philo)
// {
// 	prtinf("time to sleep\n");
// }
// void	to_eat(t_philo *philo)
// {
// 	prtinf("time to eat\n");
// }


void	to_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->print_mutex);
	printf("Philosopher %d is thinking\n", philo->philo_id);
	pthread_mutex_unlock(&philo->program->print_mutex);
}

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_program *program = philo->program;
	
	while (program->death_flag == 0 && 
		(program->times_to_eat == -1 || philo->meal_count < program->times_to_eat))
	{
		// 1. Think
		to_think(philo);
		// 2. Take forks (mutex lock)
		// 3. Eat
		// 4. Release forks (mutex unlock)
		// 5. Sleep
	}
	return (NULL);
}

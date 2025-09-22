/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:37:45 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/22 11:29:01 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_meals_eaten(t_program *program)
{
	int	i;
	int	all_done;

	i = 0;
	all_done = 1;
	while (i < program->philo_count)
	{
		pthread_mutex_lock(&program->philos[i].meal_mutex);
		if (program->philos[i].meal_count < program->times_to_eat)
			all_done = 0;
		pthread_mutex_unlock(&program->philos[i].meal_mutex);
		i++;
	}
	return (all_done);
}

int	check_death_flag(t_program *program)
{
	int	continue_flag;

	pthread_mutex_lock(&program->death_mutex);
	continue_flag = !program->death_flag;
	pthread_mutex_unlock(&program->death_mutex);
	return (continue_flag);
}

static void	philo_solo(t_program *program, t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_unlock(philo->left_fork);
	sleep_monitor(program->time_to_die, program);
	print_action(philo, "died");
	return ;
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	t_program	*program;

	philo = (t_philo *)arg;
	program = philo->program;
	if (program->philo_count == 1)
		philo_solo(program, philo);
	if (philo->philo_id % 2 == 0)
		usleep(20);
	while (check_death_flag(program))
	{
		if (program->times_to_eat != -1 && check_meals_eaten(program))
			break ;
		to_eat(philo);
		to_sleep(philo);
		to_think(philo);
	}
	return (NULL);
}

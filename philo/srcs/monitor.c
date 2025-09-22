/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:32:19 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/22 11:48:05 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleep_monitor(long long duration, t_program *program)
{
	long long	start;
	long long	current;
	int			dead;

	start = get_current_time();
	current = start;
	dead = 0;
	while (current - start < duration)
	{
		pthread_mutex_lock(&program->death_mutex);
		dead = program->death_flag;
		pthread_mutex_unlock(&program->death_mutex);
		if (dead)
			break ;
		usleep(100);
		current = get_current_time();
	}
}

static int	check_philo_death(t_philo *philo, t_program *program)
{
	long long	current_time;
	int			died;

	pthread_mutex_lock(&philo->meal_mutex);
	current_time = get_current_time();
	died = (current_time - philo->meal_last > program->time_to_die);
	pthread_mutex_unlock(&philo->meal_mutex);
	if (died)
	{
		print_action(philo, "died");
		pthread_mutex_lock(&program->death_mutex);
		program->death_flag = 1;
		pthread_mutex_unlock(&program->death_mutex);
	}
	return (died);
}

static int	check_all_philos(t_program *program)
{
	int	i;
	int	done_eating;
	int	meals;

	i = 0;
	done_eating = 1;
	while (i < program->philo_count)
	{
		pthread_mutex_lock(&program->philos[i].meal_mutex);
		meals = program->philos[i].meal_count;
		pthread_mutex_unlock(&program->philos[i].meal_mutex);
		if (check_philo_death(&program->philos[i], program))
			return (-1);
		if (program->times_to_eat == -1 || meals < program->times_to_eat)
			done_eating = 0;
		i++;
	}
	return (done_eating);
}

void	*monitor_routine(void *arg)
{
	t_program	*program;
	int			done_eating;

	program = (t_program *)arg;
	while (check_death_flag(program))
	{
		done_eating = check_all_philos(program);
		if (done_eating == -1 || done_eating == 1)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

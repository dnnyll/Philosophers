/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:37:45 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/12 15:22:36 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void print_action(t_philo *philo, const char *action)
{
	t_program *program = philo->program;

	if (program->death_flag)
		return;

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
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken the right fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken the left fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken the left fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken the right fork");
	}
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	to_think(t_philo *philo)
{
	t_program *program = philo->program;
	if (program->death_flag)
		return ;
	pthread_mutex_lock(&program->print_mutex);
	if (!program->death_flag)
		printf("%lld Philosopher %d is thinking\n",
			get_current_time() - program->start_time,
			philo->philo_id);
	pthread_mutex_unlock(&program->print_mutex);
	sleep_monitor(50, program);
}

void to_eat(t_philo *philo)
{
	t_program *program = philo->program;
	if (program->death_flag)
	return ;
	
	take_forks(philo); // lock forks + print fork actions
	
	philo->meal_last = get_current_time();
	philo->meal_count++;
	
	print_action(philo, "is eating");
	// printf("meal_count: %d\n", philo->meal_count);
	sleep_monitor(program->time_to_eat, program); // responsive sleep
	release_forks(philo); // unlock forks
}

void	to_sleep(t_philo *philo)
{
	t_program *program = philo->program;
	if (program->death_flag)
	return;
	
	print_action(philo, "is sleeping");
	sleep_monitor(program->time_to_sleep, program); // responsive sleep
}

void	*philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_program *program = philo->program;
	
	// if (philo->philo_id % 2 == 0)
	// usleep(50); // adjust duration as needed
	
	while (!program->death_flag &&
		(program->times_to_eat == -1 || philo->meal_count < program->times_to_eat))
		{
			if (program->death_flag) break;
			to_eat(philo);   // take forks, eat, release forks
			if (program->death_flag) break;
			to_sleep(philo); // sleep
			if (program->death_flag) break;
			to_think(philo); // think
			if (program->death_flag) break;
		}
		return NULL;
	}

//note: i need a while loop to make sure all my philosophers start at the same time




	// void to_eat(t_philo *philo)
	// {
	//     if (philo->program->death_flag)
	//         return;
	
	//     take_forks(philo); // locks forks and prints fork actions
	
	//     philo->meal_last = get_current_time();
	// 	printf("last_meal philo %d : %lld\n", philo->philo_id, philo->meal_last);
	//     philo->meal_count++;
	
	//     print_action(philo, "is eating");
	//     sleep_monitor(philo->program->time_to_eat, philo->program);
	
	//     release_forks(philo); // unlock forks
	// }
	
	
	
	// void to_sleep(t_philo *philo)
	// {
		//     if (philo->program->death_flag)
		//         return;
		//     print_action(philo, "is sleeping");
		//     sleep_monitor(philo->program->time_to_sleep, philo->program);
		// }
		
		
		// void *philo_routine(void *arg)
		// {
			//     t_philo *philo = (t_philo *)arg;
			//     t_program *program = philo->program;
			
			// 	if (philo->philo_id % 2 == 0)
			//         usleep(100); // tiny delay for even philosophers
			//     while (program->death_flag == 0 &&
			//            (program->times_to_eat == -1 || philo->meal_count < program->times_to_eat))
			//     {
				//         if (program->death_flag)
			// 			break;
			// 		to_eat(philo);     // 2. Take forks, eat, release forks
			//         if (program->death_flag)
			//             break;
			//         to_think(philo);   // 1. Think
			//         if (program->death_flag)
			//             break;
			
			//         to_sleep(philo);   // 3. Sleep
			//         if (program->death_flag)
			//             break;
			//     }
			//     return NULL;
			// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:13:29 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/26 14:58:20 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_input(t_philo *philo, t_program *program, char **argv)
{
	program->philo_count = ft_atoi(argv[1]);
	program->time_to_die = ft_atoi(argv[2]);
	program->time_to_eat = ft_atoi(argv[3]);
	program->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		program->times_to_eat = ft_atoi(argv[5]);
	else
		program->times_to_eat = -1;
	return (0);
}

int	init_philo(t_philo *philo)
{
	int	program_id = ;
}

int	init_program(t_program *program)
{
	
}

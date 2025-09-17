/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:10:31 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/17 10:08:47 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_current_time(void)
{
	struct	timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000LL) + (time.tv_usec / 1000LL));
}

long long	get_start_time(t_program *program)
{
	long long time;

	pthread_mutex_lock(&program->start_mutex);
	time = program->start_time;
	pthread_mutex_unlock(&program->start_mutex);

	return (time);
}

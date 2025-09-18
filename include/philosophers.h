/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:04:41 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/18 17:01:19 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_program	t_program;

typedef struct s_philo
{
	int				philo_id;
	int				meal_count;
	long long		meal_last;
	int				meal_limit;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	t_program		*program;
}	t_philo;

typedef struct s_program
{
	int				philo_count;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				times_to_eat;
	long long		start_time;
	int				death_flag;
	int				threads_ready;
	int				meals_end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	t_philo			*philos;
}	t_program;

//	cleanup.c
void		cleanup(t_program *program);

int			check_death_flag(t_program *program);

//	initialize.c
int			init_input(t_program *program, char **argv);
int			init_philo(t_philo *philo, t_program *program);
int			init_program(t_program *program);
t_philo		*init_all(t_program *program, char **argv);

//	monitor.c
pthread_t	start_monitor(t_program *program);
void		sleep_monitor(long long duration, t_program *program);
void		*monitor_routine(void *arg);

//	parser.c
int			verify_input_args(char **input);

//	routine.c
void		print_action(t_philo *philo, const char *action);
void		grab_forks(t_philo *philo);
void		release_forks(t_philo *philo);

//routine_actions.c
void		to_think(t_philo *philo);
void		to_eat(t_philo *philo);
void		to_sleep(t_philo *philo);
void		*philo_routine(void *arg);

//	threads.c
int			thread_create(t_program *program, t_philo *philo);
int			thread_join(t_program *program, t_philo *philo);
int			create_philosopher_threads(t_program *program, t_philo *philo);
int			create_monitor_thread(t_program *program,
				pthread_t *monitor_thread);

//	time.c
long long	get_current_time(void);

//	utils.c
int			is_valid_digit(char *arg);
int			ft_atoi(const char *str);

#endif
/*
┌───────────┬───────────────┬─────────────────────────────────┐
│ Color     │ ANSI Code      │ Meaning / Use                  │
├───────────┼───────────────┼─────────────────────────────────┤
│ WHITE     │ \033[0;37m    │ Normal text / philosophers full │
│ RED       │ \033[0;31m    │ Dead / error                    │
│ GREEN     │ \033[0;32m    │ Thinking / ok                   │
│ YELLOW    │ \033[0;33m    │ Fork taken / warning            │
│ BLUE      │ \033[0;34m    │ Sleeping / info                 │
│ MAGENTA   │ \033[0;35m    │ Eating / active                 │
├───────────┴───────────────┴─────────────────────────────────┤
│ How it works:                                               │
│ 1. \033[ starts the escape sequence                         │
│ 2. 0 = normal, 1 = bold/bright, etc.                        │
│ 3. 30-37 = foreground colors (black-white)                  │
│ 4. m ends the code and applies it                           │
│ 5. Reset color with \033[0m after printing                  │
└─────────────────────────────────────────────────────────────┘
*/

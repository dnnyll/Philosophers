#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	int				philo_id;
	int				meal_count;
	long long		meal_last;
	pthread_t		thread;
	// pthread_mutex_t	*fork_lock;
	pthread_mutex_t	*left_fork;		//int?
	pthread_mutex_t	*right_fork;	//int?
	size_t			start_time;
	t_program	*program;
}	t_philo;

typedef struct	s_program
{
	int				philo_count;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			times_to_eat;
	int				death_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	// long start_time; (when sim begins → for timestamps).
	// pthread_mutex_t *forks; (array of mutexes, one per fork).
	// pthread_mutex_t print_lock; (so logs don’t overlap).
	// int dead_flag; (stop program when someone dies).
}	t_program;

//	initialize.c
int	init_input(t_philo *philo, t_program *program, char **argv);
int	init_philo(t_philo *philo);
int	init_program(t_program *program);

//	parser.c
int	verify_input_args(char **input);

//	utils.c
int	is_valid_digit(char *arg);
int	ft_atoi(const char *str);

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

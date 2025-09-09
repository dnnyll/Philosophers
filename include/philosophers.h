#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_program t_program;

typedef struct s_philo
{
	int				philo_id;
	int				meal_count;
	long long		meal_last;
	int				meal_limit;	//flag to identify if max number of meals have been reached
	pthread_t		thread;
	// pthread_mutex_t	*fork_lock;
	pthread_mutex_t	*left_fork;		//int?
	pthread_mutex_t	*right_fork;	//int?
	t_program		*program;
}	t_philo;

typedef struct	s_program
{
	int				philo_count;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				times_to_eat;
	long long		start_time; //(when sim begins → for timestamps).
	int				death_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	t_philo			*philos;
	// pthread_mutex_t *forks; (array of mutexes, one per fork).
	// pthread_mutex_t print_lock; (so logs don’t overlap).
	// int dead_flag; (stop program when someone dies).
}	t_program;

//	initialize.c
int		init_input(t_program *program, char **argv);
int	init_philo(t_philo *philo, t_program *program);
int		init_program(t_program *program);
t_philo	*init_all(t_program *program, char **argv);

//	memory_utils.c
void	free_program(t_program *program);

//	monitor.c
void sleep_monitor(long long duration, t_program *program);
int start_monitor(t_program *program);
void *monitor_routine(void *arg);

//	parser.c
int	verify_input_args(char **input);

//	routine.c
void print_action(t_philo *philo, const char *action);
void take_forks(t_philo *philo);
void release_forks(t_philo *philo);


void	to_think(t_philo *philo);
void	to_eat(t_philo *philo);
void	to_sleep(t_philo *philo);
void	*philo_routine(void *arg);

//	threads.c
int	thread_create(t_program *program, t_philo *philo);
int	thread_join(t_program *program, t_philo *philo);

//	time.c
long long	get_current_time(void);

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

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data
{
	int	*counter;
	int	increments;
	pthread_mutex_t *mutex;
}	t_data;

int	increments_per_thread()
{

	return();
}

int	main(void)
{
	int				counter;
	int				i;
	pthread_mutex_t	mutex;
	pthread_t		threads[3];
	t_data			thread_data[3];

    // TODO: initialize mutex
	i = 0;
	if(pthread_mutex_init(&mutex, NULL) != 0)
	{
		printf("error: pthread_mutex_init failed\n");
		return (1);
	}

    // TODO: prepare thread_data for each thread
	while (i < 3)
	{
		thread_data[i].counter = &counter;
		thread_data[i].increments = increments_per_thread;
		thread_data[i].mutex = &mutex;
	}


	// TODO: create threads
    // TODO: wait for threads to finish
    // TODO: destroy mutex
    // TODO: print final counter

	counter = 0;
	return (0);
}
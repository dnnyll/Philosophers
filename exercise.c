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

void *create_thread(void *arg) // must return void *
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	printf("Thread started: increments = %d\n", data->increments);

	i = 0;
	while (i < data->increments)
	{
		pthread_mutex_lock(data->mutex); // lock before critical section
		*(data->counter) += 1;
		if (i % 250 == 0) // not too spammy
			printf("Thread %p incremented counter to %d\n",
			       (void *)pthread_self(), *(data->counter));
		pthread_mutex_unlock(data->mutex); // unlock after critical section
		i++;
	}
	printf("Thread finished: final counter = %d\n", *(data->counter));
	return (NULL);
}

int	main(void)
{
	int				counter;
	int				i;
	pthread_mutex_t	mutex;
	pthread_t		threads[3];
	t_data			thread_data[3];

	counter = 0;
	printf("Main: counter initialized to %d\n", counter);

	if (pthread_mutex_init(&mutex, NULL) != 0)
	{
		printf("Main: error -> pthread_mutex_init failed\n");
		return (1);
	}
	printf("Main: mutex initialized\n");

	// prepare thread_data
	i = 0;
	while (i < 3)
	{
		thread_data[i].counter = &counter;
		thread_data[i].increments = 10000000;
		thread_data[i].mutex = &mutex;
		printf("Main: thread_data[%d] prepared (increments=%d)\n",
		       i, thread_data[i].increments);
		i++;
	}

	// create threads
	i = 0;
	while (i < 3)
	{
		printf("Main: creating thread %d\n", i);
		pthread_create(&threads[i], NULL, create_thread, &thread_data[i]);
		i++;
	}

	// wait for threads
	i = 0;
	while (i < 3)
	{
		printf("Main: waiting for thread %d to finish\n", i);
		pthread_join(threads[i], NULL);
		printf("Main: thread %d joined\n", i);
		i++;
	}

	pthread_mutex_destroy(&mutex);
	printf("Main: mutex destroyed\n");

	printf("Main: Final counter value = %d\n", counter);

	return (0);
}

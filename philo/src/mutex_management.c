#include "../include/philo.h"

void		lock_forks(pthread_mutex_t *left_fork, pthread_mutex_t *right_fork, int id)
{
	struct timeval	fork_time;

	pthread_mutex_lock(left_fork);
	gettimeofday(&fork_time, NULL);
	printf("%ld %d has taken a fork\n", fork_time.tv_usec * 1000, id);
	//printf("Fork: %p\n", (void *)left_fork);
	pthread_mutex_lock(right_fork);
	gettimeofday(&fork_time, NULL);
	printf("%ld %d has taken a fork\n", fork_time.tv_usec * 1000, id);
	//printf("Fork: %p\n", (void *)right_fork);
}

void		unlock_forks(pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	struct timeval	fork_time;

	pthread_mutex_unlock(left_fork);
	gettimeofday(&fork_time, NULL);
	pthread_mutex_unlock(right_fork);
	gettimeofday(&fork_time, NULL);
}

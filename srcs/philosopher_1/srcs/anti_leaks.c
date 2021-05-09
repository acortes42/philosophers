#include "../includes/philosophers.h"

int	ft_free_all(s_data *philo)
{
	int	x;

	x = 0;
	if (philo->stats->fork)
	{
		while (x < philo->stats->number_of_philo)
		{
			pthread_mutex_destroy(&philo->stats->fork[x]);
			x++;
		}
		free(philo->stats->fork);
	}
	pthread_mutex_destroy(&philo->stats->write_fd_1);
	return (1);
}

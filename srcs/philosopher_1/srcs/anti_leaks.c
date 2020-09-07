#include "../includes/philosophers.h"

int	free_stats(s_stats *stats)
{
	int	x;

	x = 0;
	while (x < stats->number_of_philo)
	{
		if (&stats->fork_left[x])
        	pthread_mutex_destroy(&stats->fork_left[x]);
		if (&stats->fork_right[x])
        	pthread_mutex_destroy(&stats->fork_right[x]);
		x++;
	}
	if (stats->fork_left)
		free(stats->fork_left);
	if (stats->fork_right)
		free(stats->fork_right);
	if (stats)
		free(stats);
	return (1);
}

int free_philo(s_data **philo, s_stats *stats)
{
    int x;

    x = 0;
	while (x < stats->number_of_philo)
	{
		free_stats(philo[x]->stats);
		if (philo[x])
        	free(philo[x]);
		x++;
	}
	if (philo)
		free(philo);
	return (0);
}
#include "../includes/philosophers.h"

int	free_stats(s_stats *stats)
{
	int	x;

	x = 0;
	while (x < stats->number_of_philo)
	{
        pthread_mutex_destroy(stats->left[x]);
        pthread_mutex_destroy(stats->right[x]);
		free(stats->left[x]);
		free(stats->right[x]);
		x++;
	}
	free(stats->left);
	free(stats->right);
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
		x++;
        free(philo[x]);
	}
	if (philo)
		free(philo);
	return (0);
}
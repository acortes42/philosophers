#include "../includes/philosophers.h"

int				ft_change_to_int(char *str, long *nb)
{
	if (*str == '\0')
		return (-1);
	*nb = 0;
	while (*str && *str >= '0' && *str <= '9')
		*nb = 10 * *nb + (*str++ - '0');
	if (*str != '\0')
		return (-1);
	return (0);
}

int init_stats(int argc, char **argv, s_stats *stats)
{
    int x;

    x = 0;
    if (argc < 4)
        return (0);
    ft_change_to_int(argv[1], (long *)&stats->number_of_philo);
    ft_change_to_int(argv[2], &stats->time_to_die);
    ft_change_to_int(argv[3], &stats->time_eating);
    ft_change_to_int(argv[4], &stats->time_sleeping);
    if (!(stats->left = malloc(sizeof(pthread_mutex_t*) * stats->number_of_philo)) ||
        !(stats->right = malloc(sizeof(pthread_mutex_t*) * stats->number_of_philo)))
        return (-1);
    if (argv[5])
        ft_change_to_int(argv[5],(long *)&stats->times_eating);
    else
        stats->times_eating = -1;
    while (x < stats->number_of_philo)
    {
        if (!(stats->left[x] = malloc(sizeof(pthread_mutex_t))) ||
             !(stats->right[x] = malloc(sizeof(pthread_mutex_t))))
            return (-1);
        pthread_mutex_init(stats->left[x], NULL);
        pthread_mutex_init(stats->right[x], NULL);
        x++;
    }
    return (1);
}


int     main(int argc, char **argv)
{
    s_stats         *stats;
    s_data          **philo;
    int             x;

    x  = 0;
    if (!(stats = malloc(sizeof(s_stats))) || init_stats(argc, argv, stats) < 0 ||
            !(philo = malloc(sizeof(s_data *))))
        return (-1);
    while (x < stats->number_of_philo)
    {
        philo[x] = malloc(sizeof(s_data));
        a_philo_has_born(stats, philo, x);
        x++;
    }
    if (philo[x]->philo_nb == stats->number_of_philo)
        pthread_join(philo[x]->thread, NULL);
    msg_write("END\n");
    free_stats(stats);
    free_philo(philo, stats);
    system("leaks");
}
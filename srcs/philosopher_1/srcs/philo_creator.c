#include "../includes/philosophers.h"

/* 
    Problema para pensar una forma en que funcionen correctamente los cerrojos.
*/

int     go_sleep(s_data *philo)
{
    struct timeval  start;

    console_info(philo->philo_nb, "is sleeping\n", philo->stats->write_fd_1);
    gettimeofday(&start, NULL);
    while (1)
    {
        if (now_vs_old_time(start) > philo->stats->time_sleeping)
            break;
        if (now_vs_old_time(philo->last_meat) > philo->stats->time_to_die)
            return (-1);
    }
    return (1);
}

int     awake_to_think(s_data *philo)
{
    console_info(philo->philo_nb, "is thinking\n", philo->stats->write_fd_1);
    return (1);
}

int     breathing(s_data  *philo)
{
    if (eat(philo) > 0)
    {
        if (go_sleep(philo) <= 0)
            return (-1);
        awake_to_think(philo);
        return (1);
    }
    else
    {
        return (-1);
    }
    return (1);
}

//cuando philo hace un next el valor se va lejos

void    *summon_a_philo(void *args)
{
    s_data  *philo;

    philo = malloc(sizeof(s_data*));
    philo = (s_data*)args;
    while (breathing((philo)) > 0)
        NULL;
    console_info(philo->philo_nb, " died\n", philo->stats->write_fd_1);
    philo->stats->end_of_philo = 0;
    //free(philo);
    return (NULL);
}

int     a_philo_has_born (s_stats *stats, s_data **philo, int x)
{
    philo[x]->philo_nb = x + 1;
    philo[x]->nb_eat = 0;
    philo[x]->stats = stats;
    gettimeofday(&philo[x]->last_meat, NULL);
    pthread_create(&philo[x]->thread, NULL, &summon_a_philo, philo[x]);
    usleep(1000000);
    return (1);
}
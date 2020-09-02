#include "../includes/philosophers.h"

/* 
    Problema para pensar una forma en que funcionen correctamente los cerrojos.
*/

int     go_sleep(s_data *philo)
{
    struct timeval      start;
    struct timeval      now;

    console_info(philo->philo_nb, "is sleeping\n");
    gettimeofday(&start, NULL);
    while (1)
    {
        gettimeofday(&now, NULL);
        if (((((now.tv_sec - start.tv_sec) * 1000) + ((now.tv_usec - start.tv_usec) * 0.001)))
                > philo->stats->time_sleeping)
            break;
       if ((((now.tv_sec - philo->last_meat.tv_sec) * 1000) + ((now.tv_usec - philo->last_meat.tv_usec) * 0.001))
                > philo->stats->time_to_die)
            return (-1);
    }
    return (1);
}

int     awake_to_think(s_data *philo)
{
    console_info(philo->philo_nb, "is thinking\n");
    return (1);
}

int     breathing(s_data  *philo)
{
    if (eat(philo) > 0)
    {
        if (go_sleep(philo) <= 0)
            return (-1);
        awake_to_think(philo);
        console_info(philo->philo_nb, "CORRECT \n");
        return (1);
    }
    else
    {
        console_info(philo->philo_nb, " >>>>HERE \n");
        return (-1);
    }
    return (1);
}

//cuando philo hace un next el valor se va lejos

void    *summon_a_philo(void *args)
{
    s_data  *philo;

    philo = (s_data*)args;
    while (breathing(philo) > 0)
        NULL;
    console_info(philo->philo_nb, " died\n");
    return (NULL);
}

int     a_philo_has_born (s_stats *stats, s_data *philo, int x)
{
    philo->philo_nb = x;
    philo->nb_eat = 0;
    philo->stats = stats;
    gettimeofday(&philo->last_meat, NULL);
    pthread_create(&philo->thread, NULL, &summon_a_philo, philo);
    usleep(1000000);
    philo = philo->next;
    return (1);
}
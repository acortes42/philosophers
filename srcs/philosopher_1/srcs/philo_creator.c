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
       /* if (((now.tv_sec * 1000 + now.tv_usec * 0.001) -
            (philo->last_meat->tv_sec * 1000 + philo->last_meat->tv_usec * 0.001)) > philo->stats->time_to_die)
            return (-1);*/
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
        msg_write("va a dormir\n");
        if (go_sleep(philo) <= 0)
            return (-1);
        awake_to_think(philo);
        return (1);
    }
    else
        console_info(philo->philo_nb, "died\n");
    return (-1);
}

void    *summon_a_philo(void *args)
{
    s_data  *philo;

    philo = (s_data*)args;
    ft_putnbr_fd((int)philo->philo_nb, 1);
    msg_write("\n");
    while (breathing(philo))
    {
        msg_write("pass breath\n");
        continue;
    }
    console_info(philo->philo_nb, " died\n");
    return (NULL);
}

int     a_philo_has_born (s_stats *stats)
{
    s_data      *philo;
    static int  x;

    x++;
    if(!(philo = malloc(sizeof(s_data))))
        return (-1);
    philo->last_meat = NULL;
    philo->thread = malloc(sizeof(pthread_t));
    philo->philo_nb = x;
    if(stats->times_eating > 0)
        philo->nb_eat = stats->times_eating;
    philo->stats = stats;
    gettimeofday(philo->last_meat, NULL);
    pthread_create(philo->thread, NULL, summon_a_philo, philo);
    msg_write("jump fork\n");
    philo = philo->next;
    return (1);
}
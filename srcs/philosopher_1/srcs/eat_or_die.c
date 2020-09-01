#include "../includes/philosophers.h"

//Debería dar problemas si muere mientras busca un tenedor y estoy casi seguro que el
//planteamiento de los mutex tiene un error por no estar todos mirando al mismo sitio.

int     fight_for_forks(s_data *philo)
{
    int     flag;

    flag = philo->philo_nb == philo->stats->number_of_philo ? 1 : 0;
    flag = philo->philo_nb == 0 ? 2 : flag;
    console_info(philo->philo_nb, "want to take a fork\n");
    if (flag == 1)
    {
        msg_write("flag 1 running\n");
        pthread_mutex_lock(philo->stats->right[philo->philo_nb - 1]);
        pthread_mutex_lock(philo->stats->right[philo->philo_nb - 2]);
        pthread_mutex_lock(philo->stats->left[philo->philo_nb - 1]);
        pthread_mutex_lock(philo->stats->left[0]);
        msg_write("flag 1 running\n");
    }
    else if (flag == 2)
    {
        msg_write("flag 2 running\n");
        pthread_mutex_lock(philo->stats->right[philo->stats->number_of_philo - 1]);
        pthread_mutex_lock(philo->stats->right[philo->philo_nb - 1]);
        pthread_mutex_lock(philo->stats->left[philo->philo_nb - 1]);
        pthread_mutex_lock(philo->stats->left[philo->philo_nb]);
        msg_write("flag 2 running\n");
    }
    else
    {
        msg_write("flag otra running\n");
        pthread_mutex_lock(philo->stats->right[philo->philo_nb]);
        pthread_mutex_lock(philo->stats->right[philo->philo_nb - 1]);
        pthread_mutex_lock(philo->stats->left[philo->philo_nb - 1]);
        pthread_mutex_lock(philo->stats->left[philo->philo_nb]);
        msg_write("flag otra running\n");
    }
    console_info(philo->philo_nb, "have a fork and go to eat\n");
    return (1);
}

int     start_eating(s_data *philo)
{
    struct timeval *now;
    long            x;

    now = NULL;
    gettimeofday(now, NULL);
    x = philo->last_meat->tv_sec * 1000 + philo->last_meat->tv_usec * 0.001;
    if (((now->tv_sec * 1000 + now->tv_usec * 0.001) - x) < philo->stats->time_to_die)
    {
        philo->last_meat = now;
        usleep(philo->stats->time_eating * 1000);
    }
    else
    {
        console_info(philo->philo_nb, "is dead\n");
        return (-1);
    }
    return (1);
}

int     return_forks(s_data *philo)
{
        int     flag;

    flag = philo->philo_nb == philo->stats->number_of_philo ? 1 : 0;
    flag = philo->philo_nb == 0 ? 2 : flag;
    console_info(philo->philo_nb, "want to return the forks\n");
    if (flag == 1)
    {
        pthread_mutex_unlock(philo->stats->right[philo->philo_nb - 1]);
        pthread_mutex_unlock(philo->stats->right[philo->philo_nb - 2]);
        pthread_mutex_unlock(philo->stats->left[philo->philo_nb - 1]);
        pthread_mutex_unlock(philo->stats->left[0]);
    }
    else if (flag == 2)
    {
        pthread_mutex_unlock(philo->stats->right[philo->stats->number_of_philo - 1]);
        pthread_mutex_unlock(philo->stats->right[philo->philo_nb - 1]);
        pthread_mutex_unlock(philo->stats->left[philo->philo_nb - 1]);
        pthread_mutex_unlock(philo->stats->left[philo->philo_nb]);
    }
    else
    {
        pthread_mutex_unlock(philo->stats->right[philo->philo_nb]);
        pthread_mutex_unlock(philo->stats->right[philo->philo_nb - 1]);
        pthread_mutex_unlock(philo->stats->left[philo->philo_nb - 1]);
        pthread_mutex_unlock(philo->stats->left[philo->philo_nb]);
    }
    console_info(philo->philo_nb, "return the forks\n");
    return (1);
}

int     eat(s_data *philo)
{
    console_info(philo->philo_nb, " is hungry\n");
    if (!(fight_for_forks(philo) || !(start_eating(philo))))
        return (-1);
    return_forks(philo);
    return (1);
}
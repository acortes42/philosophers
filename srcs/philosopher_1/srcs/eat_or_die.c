#include "../includes/philosophers.h"

//Debería dar problemas si muere mientras busca un tenedor y estoy casi seguro que el
//planteamiento de los mutex tiene un error por no estar todos mirando al mismo sitio.

// Problema cuando dos fork se bloquean entre ellos

int     secured_lock (s_data *philo, int flag)
{
    console_info(philo->philo_nb, "impar\n", philo->stats->write_fd_1);
        if (flag == 1)
        {
            pthread_mutex_lock(&philo->stats->fork_right[philo->philo_nb - 2]);
            console_info(philo->philo_nb, "has taken right fork\n", philo->stats->write_fd_1);
            pthread_mutex_lock(&philo->stats->fork_left[0]);
            console_info(philo->philo_nb, "has taken left fork\n", philo->stats->write_fd_1);
            pthread_mutex_lock(&philo->stats->fork_right[philo->philo_nb - 1]);
            pthread_mutex_lock(&philo->stats->fork_left[philo->philo_nb - 1]);
        }
        else if (flag == 2)
        {
            pthread_mutex_lock(&philo->stats->fork_right[philo->stats->number_of_philo - 1]);
            console_info(philo->philo_nb, "has taken right fork\n", philo->stats->write_fd_1);
            pthread_mutex_lock(&philo->stats->fork_left[philo->philo_nb]);
            console_info(philo->philo_nb, "has taken left fork\n", philo->stats->write_fd_1);
            pthread_mutex_lock(&philo->stats->fork_right[0]);
            pthread_mutex_lock(&philo->stats->fork_left[0]);
        }
        else
        {
            pthread_mutex_lock(&philo->stats->fork_right[philo->philo_nb - 2]);
            console_info(philo->philo_nb, "has taken right fork\n", philo->stats->write_fd_1);
            pthread_mutex_lock(&philo->stats->fork_left[philo->philo_nb]);
            console_info(philo->philo_nb, "has taken left fork\n", philo->stats->write_fd_1);
            pthread_mutex_lock(&philo->stats->fork_right[philo->philo_nb - 1]);
            pthread_mutex_lock(&philo->stats->fork_left[philo->philo_nb - 1]);
        }
        console_info(philo->philo_nb, "end fork\n", philo->stats->write_fd_1);
        return (1);
}

int     fight_for_forks(s_data *philo)
{
    int     flag;

    flag = philo->philo_nb == philo->stats->number_of_philo ? 1 : 0;
    flag = philo->philo_nb == 1 ? 2 : flag;
    if (ask_if_alive(philo) < 0) 
        return (-1);
    if ((philo->philo_nb % 2) == 0)
    {
        console_info(philo->philo_nb, "par\n", philo->stats->write_fd_1);
        if (flag == 1)
        {
            pthread_mutex_lock(&philo->stats->fork_right[philo->philo_nb - 1]);
            pthread_mutex_lock(&philo->stats->fork_left[philo->philo_nb - 1]);
            pthread_mutex_lock(&philo->stats->fork_left[0]);
            console_info(philo->philo_nb, "has taken left fork\n", philo->stats->write_fd_1);
            pthread_mutex_lock(&philo->stats->fork_right[philo->philo_nb - 2]);
            console_info(philo->philo_nb, "has taken right fork\n", philo->stats->write_fd_1);
        }
    /*    else if (flag == 2)
        {
            pthread_mutex_lock(&philo->stats->fork_left[philo->philo_nb - 1]);
            pthread_mutex_lock(&philo->stats->fork_right[philo->stats->number_of_philo - 1]);
            pthread_mutex_lock(&philo->stats->fork_right[philo->philo_nb - 1]);
            pthread_mutex_lock(&philo->stats->fork_left[philo->philo_nb]);
        }*/
        else
        {
            pthread_mutex_lock(&philo->stats->fork_left[philo->philo_nb - 1]);
            pthread_mutex_lock(&philo->stats->fork_right[philo->philo_nb - 1]);
            pthread_mutex_lock(&philo->stats->fork_left[philo->philo_nb]);
            console_info(philo->philo_nb, "has taken left fork\n", philo->stats->write_fd_1);
            pthread_mutex_lock(&philo->stats->fork_right[philo->philo_nb - 2]);
            console_info(philo->philo_nb, "has taken right fork\n", philo->stats->write_fd_1);
        }
        console_info(philo->philo_nb, "end fork\n", philo->stats->write_fd_1);
    }
    else
        secured_lock(philo, flag);
    return (1);
}

// CALCULO ERRONEO, mirar ask_if_alive

int     start_eating(s_data *philo)
{
    struct timeval  now;

    gettimeofday(&now, NULL);
    console_info(philo->philo_nb, " is eating\n", philo->stats->write_fd_1);
    if (now_vs_old_time(philo->last_meat) < philo->stats->time_to_die)
    {
        philo->last_meat = now;
        usleep(philo->stats->time_eating * 1000);
    }
    else
        return (-1);
    philo->nb_eat++;
    return (1);
}

int     return_forks(s_data *philo)
{
    int     flag;

    flag = philo->philo_nb == philo->stats->number_of_philo ? 1 : 0;
    flag = philo->philo_nb == 1 ? 2 : flag;
    if (flag == 1)
    {
        pthread_mutex_unlock(&philo->stats->fork_left[philo->philo_nb - 1]);
        pthread_mutex_unlock(&philo->stats->fork_right[philo->philo_nb - 1]);
        pthread_mutex_unlock(&philo->stats->fork_left[0]);
        pthread_mutex_unlock(&philo->stats->fork_right[philo->philo_nb - 2]);
    }
    else if (flag == 2)
    {
        pthread_mutex_unlock(&philo->stats->fork_left[philo->philo_nb - 1]);
        pthread_mutex_unlock(&philo->stats->fork_right[philo->philo_nb - 1]);
        pthread_mutex_unlock(&philo->stats->fork_left[philo->philo_nb]);
        pthread_mutex_unlock(&philo->stats->fork_right[philo->stats->number_of_philo - 1]);
    }
    else
    {
        pthread_mutex_unlock(&philo->stats->fork_left[philo->philo_nb - 1]);
        pthread_mutex_unlock(&philo->stats->fork_right[philo->philo_nb - 1]);
        pthread_mutex_unlock(&philo->stats->fork_left[philo->philo_nb]);
        pthread_mutex_unlock(&philo->stats->fork_right[philo->philo_nb - 2]);
    }
    console_info(philo->philo_nb, " return a fork\n", philo->stats->write_fd_1);
    return (1);
}

int     eat(s_data *philo)
{
    if (philo->stats->times_eating >= 0)
        if (philo->nb_eat >= philo->stats->times_eating)
            return (-1);
    if (fight_for_forks(philo) < 0 || start_eating(philo) < 0)
        return (-1);
    return_forks(philo);
    return (1);
}
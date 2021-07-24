#include "../includes/philosophers.h"

//Cambiamos toda la logica de la pelea por los tenedores por refactorización del código

int     fight_for_forks(s_data *philo)
{
    if (philo->stats->end_of_philo <= 0)
        return (-1);
    pthread_mutex_lock(&philo->stats->fork[philo->philo_nb - 1]);
    printf(_YELLOW);
    if (philo->stats->end_of_philo > 0)
        console_info(philo->philo_nb, " has taken a fork\n", philo->stats->write_fd_1, philo->stats->program_timer);
    pthread_mutex_lock(&philo->stats->fork[(philo->philo_nb) % philo->stats->number_of_philo]);
    printf(_YELLOW);
    if (philo->stats->end_of_philo > 0)
        console_info(philo->philo_nb, " has taken a fork\n", philo->stats->write_fd_1, philo->stats->program_timer);
    return (1);
}

// CALCULO ERRONEO, mirar ask_if_alive

int     start_eating(s_data *philo)
{
    pthread_mutex_lock(&philo->stats->life);
    printf(_GREEN);
    if (philo->stats->end_of_philo > 0)
    {
        philo->timer = ft_tempo();
        console_info(philo->philo_nb, " is eating\n", philo->stats->write_fd_1, philo->stats->program_timer);
        philo->timer = ft_tempo();
        usleep(philo->stats->time_eating * 1000);
    }
    pthread_mutex_unlock(&philo->stats->life);
    philo->nb_eat++;
    //aqui le asignamos valor a tempos para decirle que ya ha cómido y que, por ahora, no va a morir.
    //y aqui, si hemos creado mutex para comer, lo liberamos.
    return (1);
}

int     return_forks(s_data *philo)
{
    printf(_CYAN);
    pthread_mutex_unlock(&philo->stats->fork[philo->philo_nb - 1]);
    pthread_mutex_unlock(&philo->stats->fork[(philo->philo_nb) % philo->stats->number_of_philo]);
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
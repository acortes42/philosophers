#include "../includes/philosophers.h"

//Cambiamos toda la logica de la pelea por los tenedores por refactorización del código

int     fight_for_forks(s_data *philo)
{
    if (philo->stats->end_of_philo <= 0)
        return (-1);
    if ((ft_tempo() - philo->program_timer) > philo->stats->time_to_die)
        return (-1);
    pthread_mutex_lock(&philo->stats->fork[philo->stats->value_lfork]);
   /* if ((ft_tempo() - philo->program_timer) > philo->stats->time_to_die)
    {   
        pthread_mutex_unlock(&philo->stats->fork[philo->stats->value_lfork]);
        return (-1);
    }*/
    printf(_YELLOW);
    if (philo->stats->end_of_philo > 0)
        console_info(philo->philo_nb, " has taken a fork\n", philo->stats->write_fd_1, philo->stats->timer);
    pthread_mutex_lock(&philo->stats->fork[philo->stats->value_rfork]);
  /*  if ((ft_tempo() - philo->program_timer) > philo->stats->time_to_die)
    {
         pthread_mutex_unlock(&philo->stats->fork[philo->stats->value_lfork]);
        pthread_mutex_unlock(&philo->stats->fork[philo->stats->value_rfork]);
        return (-1);
    }*/
    printf(_YELLOW);
    if (philo->stats->end_of_philo > 0)
        console_info(philo->philo_nb, " has taken a fork\n", philo->stats->write_fd_1, philo->stats->timer);
    return (1);
}

// CALCULO ERRONEO, mirar ask_if_alive

int     start_eating(s_data *philo)
{
    printf(_GREEN);
    if (philo->stats->end_of_philo > 0)
    {
        console_info(philo->philo_nb, " is eating\n", philo->stats->write_fd_1, philo->stats->timer);
        usleep(philo->stats->time_eating * 1000);
    }
    philo->nb_eat++;
    //aqui le asignamos valor a tempos para decirle que ya ha cómido y que, por ahora, no va a morir.
    //y aqui, si hemos creado mutex para comer, lo liberamos.
    return (1);
}

int     return_forks(s_data *philo)
{
    printf(_CYAN);
    pthread_mutex_unlock(&philo->stats->fork[philo->stats->value_lfork]);
    pthread_mutex_unlock(&philo->stats->fork[philo->stats->value_rfork]);
    return (1);
}


int     eat(s_data *philo)
{
    if (philo->stats->times_eating >= 0)
        if (philo->nb_eat >= philo->stats->times_eating)
            return (-1);
    if (fight_for_forks(philo) < 0 || start_eating(philo) < 0)
        return (-1);
    philo->program_timer = ft_tempo();
    return_forks(philo);
    return (1);
}
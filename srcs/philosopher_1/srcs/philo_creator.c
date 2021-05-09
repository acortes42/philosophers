/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 14:54:52 by acortes-          #+#    #+#             */
/*   Updated: 2021/05/09 19:12:49 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int     go_sleep(s_data *philo)
{
    printf(_BLUE);
    if (philo->stats->end_of_philo > 0) 
        console_info(philo->philo_nb, "is sleeping\n", philo->stats->write_fd_1, philo->stats->timer);
    if (philo->stats->time_to_die > philo->stats->time_sleeping)
            usleep(philo->stats->time_sleeping * 1000);
    else
    {
        usleep(philo->stats->time_to_die * 1000);
        return (-1);
    }
    return (1);
}

int     breathing(s_data  *philo)
{
    if (philo->stats->end_of_philo > 0 && eat(philo) > 0)
    {
        if (go_sleep(philo) <= 0)
            return (-1);
        printf(_YELLOW);
        if (philo->stats->end_of_philo > 0) 
            console_info(philo->philo_nb, "is thinking\n", philo->stats->write_fd_1, philo->stats->timer);
        return (1);
    }
    else
        return (-1);
    return (1);
}

void    *summon_a_philo(void *args)
{
    s_data  *philo;

    philo = malloc(sizeof(s_data*));
    philo = (s_data*)args;
    printf(_MAGENTA);
    philo->program_timer = ft_tempo();
    while (breathing((philo)) > 0)
        NULL;
    if (philo->stats->end_of_philo <= 0)
        return (NULL);
    if (philo->stats->times_eating > 0 && philo->nb_eat >= philo->stats->times_eating)
    {
        console_info(philo->philo_nb, " survive the festival\n", philo->stats->write_fd_1, philo->stats->timer);
        philo->stats->end_of_philo = 0;
        return (NULL);
    }
    printf(_RED);
    console_info(philo->stats->number_of_philo, " died\n", philo->stats->write_fd_1, philo->stats->timer);
    philo->stats->end_of_philo = 0;
   // free(philo);
    return (NULL);
}

int     a_philo_has_born (s_stats *stats, s_data **philo, int x)
{
    philo[x]->philo_nb = x + 1;
    philo[x]->nb_eat = 0;
    philo[x]->stats = stats;
    philo[x]->stats->value_lfork = x;
    philo[x]->stats->value_rfork = (x + 1) % stats->number_of_philo;
    pthread_create(&philo[x]->thread, NULL, &summon_a_philo, philo[x]);
    usleep(10000);
    return (1);
}
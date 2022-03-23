/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 14:54:52 by acortes-          #+#    #+#             */
/*   Updated: 2022/03/23 17:51:34 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_if_end(t_data *philo)
{
	pthread_mutex_lock(&philo->stats->end_of_philo_mutex);
	if (philo->stats->end_of_philo != 0)
	{
		pthread_mutex_unlock(&philo->stats->end_of_philo_mutex);
		return(0);
	}
	pthread_mutex_unlock(&philo->stats->end_of_philo_mutex);
	return(1);
}

int	go_sleep(t_data *philo)
{
	if (philo->end_of_this_philo != 0)
	{
		if (check_if_end(&(*philo)))
			console_info(philo->philo_nb, "is sleeping\n", &(*philo), 0);
		if (philo->time_to_die > philo->time_sleeping)
			pl_usleep(philo->stats->time_sleeping);
		else
		{
			pl_usleep(philo->time_to_die);
			philo->stats->end_of_philo = 0;
		}
	}
	return (1);
}

int	breathing(t_data *philo)
{
	if (!check_if_end(&(*philo)) && eat(philo) > 0)
	{
		if (philo->stats->all_to_eat != 0)
		{
			if (go_sleep(philo) <= 0)
				return (-1);
			if (philo->end_of_this_philo != 0)
			{
				if (check_if_end(&(*philo)))
					console_info(philo->philo_nb, "is thinking\n", &(*philo), 0);
			}
		}
	}
	else
		return (-1);
	return (1);
}

void	*summon_a_philo(void *args)
{
	t_data	*philo;

	philo = (t_data *) args;
	pthread_mutex_lock(&philo->stats->tmp_int_mutex);
	philo->timer = pl_get_time_msec();
	pthread_mutex_unlock(&philo->stats->tmp_int_mutex);
	if (!(philo->philo_nb % 2))
		pl_usleep(50);
	while (breathing((&(*philo))) > 0)
		NULL;
	philo->stats->end_of_philo = 0;
	return (NULL);
}

int	a_philo_has_born(t_stats *stats, t_data **philo, int x)
{
	philo[x]->philo_nb = x + 1;
	philo[x]->nb_eat = 0;
	philo[x]->stats = stats;
	philo[x]->end_of_this_philo = 42;
	philo[x]->stats->all_to_eat = stats->number_of_philo;
	philo[x]->number_of_philo = stats->number_of_philo;
	philo[x]->time_to_die = stats->time_to_die;
	philo[x]->time_eating = stats->time_eating;
	philo[x]->time_sleeping = stats->time_sleeping;
	philo[x]->times_eating = stats->times_eating;
	
	return (1);
}

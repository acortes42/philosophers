/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_or_die.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:58:57 by adrian            #+#    #+#             */
/*   Updated: 2022/03/23 16:05:34 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	fight_for_forks(t_data *philo)
{
	if (philo->stats->end_of_philo <= 0)
		return (-1);
	if (philo->end_of_this_philo != 0)
	{
		pthread_mutex_lock(&philo->stats->fork[philo->philo_nb - 1]);
		if (philo->stats->end_of_philo > 0)
			console_info(philo->philo_nb, " has taken a fork\n", &(*philo), 0);
	}


	if (philo->end_of_this_philo != 0)
	{
		pthread_mutex_lock(&philo->stats->fork[(philo->philo_nb) % \
				philo->stats->number_of_philo]);
		if (philo->stats->end_of_philo > 0)
			console_info(philo->philo_nb, " has taken a fork\n", &(*philo), 0);
	}
	return (1);
}

int	start_eating(t_data *philo)
{
	if (philo->stats->end_of_philo > 0 || philo->stats->all_to_eat != 0)
	{
		if (philo->end_of_this_philo != 0 && philo->stats->end_of_philo > 0)
		{
			philo->timer = pl_get_time_msec();
			console_info(philo->philo_nb, " is eating\n", &(*philo), 0);
		}
		if (philo->times_eating > 0 && \
			philo->nb_eat >= philo->times_eating - 1)
			philo->stats->all_to_eat--;
		philo->nb_eat++;
		if (philo->stats->all_to_eat == 0)
			return(0);
		pl_usleep(philo->time_eating);

		
	}
	if (philo->stats->all_to_eat == 0)
		return(0);
	return (1);
}

int	return_forks(t_data *philo)
{
	if (philo->end_of_this_philo != 0 && philo->stats->all_to_eat != 0)
	{
		pthread_mutex_unlock(&philo->stats->fork[philo->philo_nb - 1]);
		pthread_mutex_unlock(&philo->stats->fork[(philo->philo_nb) \
			% philo->stats->number_of_philo]);
	}
	return (1);
}

int	eat(t_data *philo)
{
	if (philo->times_eating > 0)
		if (philo->nb_eat >= philo->times_eating)
			return (-1);
	if (fight_for_forks(&(*philo)) < 0 || start_eating(&(*(philo))) < 0)
		return (-1);
	return_forks(&(*philo));
	return (1);
}

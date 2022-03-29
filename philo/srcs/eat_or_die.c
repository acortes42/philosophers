/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_or_die.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:58:57 by adrian            #+#    #+#             */
/*   Updated: 2022/03/29 17:21:08 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	fight_for_forks(t_data *philo)
{
	if (check_if_end(&(*philo)))
		return (-1);
	if (philo->end_of_this_philo != 0)
	{
		pthread_mutex_lock(&philo->stats->fork[philo->philo_nb - 1]);
		if (!check_if_end(&(*philo)))
			console_info(philo->philo_nb, " has taken a fork\n", &(*philo), 0);
	}
	if (philo->end_of_this_philo != 0)
	{
		pthread_mutex_lock(&philo->stats->fork[(philo->philo_nb) % \
				philo->number_of_philo]);
		if (!check_if_end(&(*philo)))
			console_info(philo->philo_nb, " has taken a fork\n", &(*philo), 0);
	}
	return (1);
}

int	start_eating(t_data *philo)
{
	if (!all_eat_is_zero(&(*philo)))
	{
		if (!check_if_end(&(*philo)))
		{
			if (philo->end_of_this_philo != 0)
			{
				philo->timer = pl_get_time_msec();
				console_info(philo->philo_nb, " is eating\n", &(*philo), 0);
			}
			if (philo->times_eating > 0 && \
				philo->nb_eat >= philo->times_eating - 1)
				reduce_all_eat(&(*philo));
			philo->nb_eat++;
			if (all_eat_is_zero(&(*philo)))
				return(0);
			pl_usleep(philo->time_eating);
		}
	}
	if (all_eat_is_zero(&(*philo)))
		return(0);
	return (1);
}

int	return_forks(t_data *philo)
{
	if (philo->end_of_this_philo != 0 && !all_eat_is_zero(&(*philo)))
	{
		pthread_mutex_unlock(&philo->stats->fork[philo->philo_nb - 1]);
		pthread_mutex_unlock(&philo->stats->fork[(philo->philo_nb) \
			% philo->number_of_philo]);
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

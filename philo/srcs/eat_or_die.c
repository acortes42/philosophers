/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_or_die.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:58:57 by adrian            #+#    #+#             */
/*   Updated: 2022/04/02 19:25:17 by acortes-         ###   ########.fr       */
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
	if (philo->number_of_philo == 1)
	{
		philo->end_of_this_philo = 0;
		pthread_mutex_unlock(&philo->stats->fork[philo->philo_nb - 1]);
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

void	aux_start_eating(t_data *philo)
{
	if (philo->end_of_this_philo != 0)
	{
		pthread_mutex_lock(&philo->stats->check_timer);
		philo->timer = pl_get_time_msec();
		pthread_mutex_unlock(&philo->stats->check_timer);
		console_info(philo->philo_nb, " is eating\n", &(*philo), 0);
	}
	if (philo->times_eating > 0 && \
		philo->nb_eat >= philo->times_eating - 1)
		reduce_all_eat(&(*philo));
	philo->nb_eat++;
}

int	start_eating(t_data *philo)
{
	int	i;

	i = -1;
	if (!all_eat_is_zero(&(*philo)))
	{
		if (!check_if_end(&(*philo)))
		{
			aux_start_eating(&(*philo));
			if (all_eat_is_zero(&(*philo)))
				return (0);
			if (philo->time_to_die > philo->time_eating)
				while (++i < philo->time_eating)
					pl_usleep(1);
			else
				pl_usleep(philo->time_to_die);
		}
	}
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
		if (all_eat_is_zero(philo))
			return (-1);
	if (fight_for_forks(&(*philo)) < 0 || start_eating(&(*(philo))) < 0)
		return (-1);
	return_forks(&(*philo));
	return (1);
}

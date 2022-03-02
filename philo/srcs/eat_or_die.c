/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_or_die.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:58:57 by adrian            #+#    #+#             */
/*   Updated: 2022/03/02 13:43:42 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	fight_for_forks(t_data *philo)
{
	if (philo->stats->end_of_philo <= 0)
		return (-1);
	pthread_mutex_lock(&philo->stats->fork[philo->philo_nb - 1]);
	printf(_YELLOW);
	if (philo->stats->end_of_philo > 0)
		console_info(philo->philo_nb, " has taken a fork\n", \
			philo->stats->write_fd_1, philo->stats->program_timer);
	pthread_mutex_lock(&philo->stats->fork[(philo->philo_nb) % \
		philo->stats->number_of_philo]);
	printf(_YELLOW);
	if (philo->stats->end_of_philo > 0)
		console_info(philo->philo_nb, " has taken a fork\n", \
			philo->stats->write_fd_1, philo->stats->program_timer);
	return (1);
}

int	start_eating(t_data *philo)
{
	pthread_mutex_lock(&philo->stats->life);
	printf(_GREEN);
	if (philo->stats->end_of_philo > 0)
	{
		philo->nb_eat++;
		if (philo->stats->times_eating > 0 && \
			philo->nb_eat >= philo->stats->times_eating)
		{
			philo->stats->end_of_philo--;
			console_info(philo->philo_nb, " is eating\n", \
				philo->stats->write_fd_1, philo->stats->program_timer);
			pthread_mutex_unlock(&philo->stats->life);
			return (1);
		}
		philo->timer = ft_tempo();
		console_info(philo->philo_nb, " is eating\n", \
			philo->stats->write_fd_1, philo->stats->program_timer);
		philo->timer = ft_tempo();
		usleep(philo->stats->time_eating * 1000);
	}
	pthread_mutex_unlock(&philo->stats->life);
	return (1);
}

int	return_forks(t_data *philo)
{
	printf(_CYAN);
	pthread_mutex_unlock(&philo->stats->fork[philo->philo_nb - 1]);
	pthread_mutex_unlock(&philo->stats->fork[(philo->philo_nb) \
		% philo->stats->number_of_philo]);
	return (1);
}

int	eat(t_data *philo)
{
	if (philo->stats->times_eating > 0)
		if (philo->nb_eat >= philo->stats->times_eating)
			return (-1);
	if (fight_for_forks(philo) < 0 || start_eating(philo) < 0)
		return (-1);
	return_forks(philo);
	return (1);
}

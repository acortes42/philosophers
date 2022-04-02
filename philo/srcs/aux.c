/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:52:54 by acortes-          #+#    #+#             */
/*   Updated: 2022/04/02 12:44:51 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	end_to_zero(t_data *philo)
{
	pthread_mutex_lock(&philo->stats->end_of_philo_mutex);
	philo->stats->end_of_philo = 0;
	pthread_mutex_unlock(&philo->stats->end_of_philo_mutex);
}

int	check_if_end(t_data *philo)
{
	pthread_mutex_lock(&philo->stats->end_of_philo_mutex);
	if (philo->stats->end_of_philo != 0)
	{
		pthread_mutex_unlock(&philo->stats->end_of_philo_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->stats->end_of_philo_mutex);
	return (1);
}

int	all_eat_is_zero(t_data *philo)
{
	pthread_mutex_lock(&philo->stats->all_to_eat_mutex);
	if (philo->stats->all_to_eat == 0)
	{
		pthread_mutex_unlock(&philo->stats->all_to_eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->stats->all_to_eat_mutex);
	return (0);
}

int	check_if_start(t_data *philo)
{
	pthread_mutex_lock(&philo->stats->tmp_int_mutex);
	if (philo->stats->tmp_int == 0)
	{
		pthread_mutex_unlock(&philo->stats->tmp_int_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->stats->tmp_int_mutex);
	return (1);
}

void	norminette_chech_if_alive(t_data *philo, long i)
{
	console_info(philo[i].philo_nb, "is dead\n", &philo[i], 1);
	end_to_zero(&philo[i]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 14:54:52 by acortes-          #+#    #+#             */
/*   Updated: 2022/04/01 14:54:37 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	reduce_all_eat(t_data *philo)
{
	pthread_mutex_lock(&philo->stats->tmp_int_mutex);
	philo->stats->all_to_eat--;
	pthread_mutex_unlock(&philo->stats->tmp_int_mutex);
	return (1);
}

void	change_tmp_int(t_stats *stats, int x)
{
	pthread_mutex_lock(&stats->tmp_int_mutex);
	stats->tmp_int = x;
	printf("wololo\n");
	pthread_mutex_unlock(&stats->tmp_int_mutex);
}

int	go_sleep(t_data *philo)
{
	int	i;

	i = -1;
	if (philo->end_of_this_philo != 0)
	{
		if (!check_if_end(&(*philo)))
			console_info(philo->philo_nb, "is sleeping\n", &(*philo), 0);
		if (philo->time_to_die > philo->time_sleeping)
			while (++i < philo->time_sleeping)
				pl_usleep(1);
	}
	return (1);
}

int	breathing(t_data *philo)
{
	if (!check_if_end(&(*philo)) && eat(philo) > 0)
	{
		if (!all_eat_is_zero(&(*philo)))
		{
			if (go_sleep(philo) <= 0)
				return (-1);
			if (philo->end_of_this_philo != 0)
			{
				if (!check_if_end(&(*philo)))
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
	philo->timer = pl_get_time_msec();
	if (!(philo->philo_nb % 2))
		pl_usleep(50);
	while (breathing((&(*philo))) > 0)
		NULL;
	end_to_zero(&(*philo));
	return (NULL);
}

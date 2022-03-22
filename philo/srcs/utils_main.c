/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 23:37:35 by adrian            #+#    #+#             */
/*   Updated: 2022/03/22 12:40:20 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_stats	*ft_return_stats(int argc, char **argv)
{
	t_stats	*stats;

	stats = malloc(sizeof(t_stats));
	if (ft_test_arguments(argc, argv) == 1 || !(stats))
		return (NULL);
	if (init_stats(argc, argv, stats) <= 0)
	{
		free(stats);
		return (NULL);
	}
	stats->end_of_philo = 42;
	return (stats);
}

int	normi_die(t_data **philo, int i)
{
	philo[i]->stats->end_of_philo = 0;
	console_info(philo[i]->philo_nb, " died\n", *philo);
	return (1);
}

void	free_stats(t_stats *stats)
{
	free(stats->fork);
	free(stats);
}

long long unsigned int	pl_timeval_to_msec(struct timeval *time)
{
	return ((time->tv_sec * 1000) + (time->tv_usec / 1000));
}

long long unsigned int	pl_get_time_msec(void)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return (pl_timeval_to_msec(&timestamp));
}


void	pl_usleep(int wait)
{
	long long unsigned int	time_end;

	time_end = pl_get_time_msec() + wait;
	while (pl_get_time_msec() < time_end)
		usleep(50);
}
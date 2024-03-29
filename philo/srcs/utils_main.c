/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 23:37:35 by adrian            #+#    #+#             */
/*   Updated: 2022/04/02 12:48:02 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_return_stats(int argc, char **argv, t_stats *stats)
{
	if (ft_test_arguments(argc, argv) == 1)
		return (0);
	if (init_stats(argc, argv, stats) <= 0)
	{
		free(stats->fork);
		return (0);
	}
	pthread_mutex_init(&stats->write_fd_1, NULL);
	pthread_mutex_init(&stats->end_of_philo_mutex, NULL);
	pthread_mutex_init(&stats->tmp_int_mutex, NULL);
	pthread_mutex_init(&stats->all_to_eat_mutex, NULL);
	pthread_mutex_init(&stats->check_timer, NULL);
	stats->end_of_philo = 42;
	return (1);
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

void	pl_usleep(long wait)
{
	long long unsigned int	time_end;

	time_end = pl_get_time_msec() + wait;
	while (pl_get_time_msec() < time_end)
		usleep(50);
}

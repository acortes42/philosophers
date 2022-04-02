/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:59:13 by adrian            #+#    #+#             */
/*   Updated: 2022/04/02 18:52:09 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_tempo(void)
{
	struct timeval	tv;
	int				i;

	gettimeofday(&tv, NULL);
	i = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (i);
}

int	ft_test_arguments(int argc, char **argv)
{
	long	x;

	x = 0;
	if ((argc != 5 && argc != 6) || ft_process_argv(argv) == 1)
	{
		printf("Incorrect arguments\n");
		return (1);
	}
	if (to_int(argv[1], &x) < 0)
		return (1);
	if (x < 1)
	{
		printf("One or more philosophers required\n");
		return (1);
	}
	return (0);
}

int	to_int(char *str, long *nb)
{
	int	x;

	x = ft_strlen(str);
	if (*str == '\0')
		return (-1);
	if (x > 7)
		return (-1);
	*nb = 0;
	while (*str && *str >= '0' && *str <= '9')
		*nb = 10 * *nb + (*str++ - '0');
	if (*str != '\0')
		return (-1);
	return (0);
}

int	init_stats(int argc, char **argv, t_stats *stats)
{
	int	x;

	x = -1;
	if (argc < 4 || to_int(argv[1], (long *)&stats->number_of_philo) == -1 || \
		stats->number_of_philo > 200 || to_int(argv[2], \
		&stats->time_to_die) == -1 || \
		to_int(argv[3], &stats->time_eating) || \
		to_int(argv[4], &stats->time_sleeping))
		return (0);
	stats->fork = malloc(sizeof(pthread_mutex_t) * stats->number_of_philo);
	if (!(stats->fork))
		return (-1);
	if (argv[5])
	{
		if (to_int(argv[5], (long *)&stats->times_eating) == -1)
			return (0);
		if (*argv[5] == '0' && strlen(argv[5]) == 1)
			return (0);
	}
	else
		stats->times_eating = -1;
	while (++x < stats->number_of_philo)
		pthread_mutex_init(&stats->fork[x], NULL);
	return (1);
}

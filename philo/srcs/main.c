/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 14:42:06 by acortes-          #+#    #+#             */
/*   Updated: 2022/03/23 20:09:10 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_process_argv(char **argv)
{
	long	x;

	x = 0;
	if (to_int(argv[1], &x) == -1)
		return (1);
	if (to_int(argv[2], &x) == -1)
		return (1);
	if (to_int(argv[3], &x) == -1)
		return (1);
	if (to_int(argv[4], &x) == -1)
		return (1);
	return (0);
}

void	check_if_alive(t_data **philo, t_stats *stats)
{
	int		check;
	int		i;

	check = 0;
	while (!check_if_end(*philo))
	{
		i = -1;
		while (++i < stats->number_of_philo && \
			!check_if_end(*philo))
		{
			pthread_mutex_lock(&stats->life);
			if (((ft_tempo() - (int)philo[i]->timer) > stats->time_to_die))
			{
				console_info(philo[i]->philo_nb, " died\n", *philo, 1);
				philo[i]->stats->end_of_philo = 0;
				check = 1;
			}
			pthread_mutex_unlock(&stats->life);
			if (check == 1)
				break ;
		}
		if (check == 1)
			break ;
	}
}

void	aux_threads(t_data **philo, t_stats *stats)
{
	int	x;

	x = -1;
	pthread_mutex_lock(&stats->tmp_int_mutex);
	while (++x < stats->number_of_philo)
		pthread_create(&philo[x]->thread, NULL, &summon_a_philo, philo[x]);
	x = -1;
	pl_usleep(500);
	pthread_mutex_unlock(&stats->tmp_int_mutex);
	stats->program_timer = pl_get_time_msec();
	check_if_alive(philo, stats);
	x = -1;
	while (++x < stats->number_of_philo)
		pthread_join(philo[x]->thread, NULL);
	x = -1;
	while (++x < stats->number_of_philo)
		pthread_mutex_destroy(&stats->fork[x]);
}

int	main(int argc, char **argv)
{
	t_stats	*stats;
	t_data	**philo;
	int		x;

	stats = ft_return_stats(argc, argv);
	if (!(stats))
		return (1);
	philo = malloc(sizeof(t_data *) * stats->number_of_philo);
	if (!(philo))
	{
		free(stats);
		return (1);
	}
	x = -1;
	while (++x < stats->number_of_philo)
	{
		philo[x] = malloc(sizeof(t_data));
		a_philo_has_born(stats, philo, x);
	}
	aux_threads(philo, stats);
	pthread_mutex_destroy(&stats->write_fd_1);
	free(philo);
	pl_usleep(500);
	free_stats(stats);
	return (1);
}

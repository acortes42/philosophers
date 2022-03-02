/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 14:42:06 by acortes-          #+#    #+#             */
/*   Updated: 2022/03/02 13:48:23 by acortes-         ###   ########.fr       */
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

void	*check_if_alive(t_data **philo)
{
	int		check;
	int		i;

	check = 0;
	while (1 == 1 && philo[0]->stats->end_of_philo != 0)
	{
		i = -1;
		while (++i < philo[0]->stats->number_of_philo && \
			philo[i]->stats->end_of_philo != 0)
		{
			pthread_mutex_lock(&philo[i]->stats->life);
			if (((ft_tempo() - philo[i]->timer) > philo[i]->stats->time_to_die))
				check = normi_die(philo, i);
			pthread_mutex_unlock(&philo[i]->stats->life);
			if (check == 1)
				break ;
			usleep(1000);
		}
		if (check == 1)
			break ;
	}
	return (NULL);
}

void	aux_threads(t_data **philo, t_stats *stats)
{
	int	x;

	x = -1;
	stats->program_timer = ft_tempo();
	while (++x < stats->number_of_philo)
	{
		pthread_create(&philo[x]->thread, NULL, &summon_a_philo, philo[x]);
		pthread_detach(philo[x]->thread);
		usleep(100);
	}
	check_if_alive(philo);
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
	sleep(1);
	free_stats(stats);
	return (1);
}

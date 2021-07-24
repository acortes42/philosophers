/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 14:42:06 by acortes-          #+#    #+#             */
/*   Updated: 2021/07/24 22:15:00 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_process_argv(char **argv)
{
	long	x;

	x = 0;
	if (ft_change_to_int(argv[1], &x) == -1)
		return (1);
	if (ft_change_to_int(argv[2], &x) == -1)
		return (1);
	if (ft_change_to_int(argv[3], &x) == -1)
		return (1);
	if (argv[4])
		if (ft_change_to_int(argv[1], &x) == -1)
			return (1);
	return (0);
}

t_stats	*ft_return_stats(int argc, char **argv)
{
	t_stats	*stats;
	int		x;

	x = -1;
	stats = malloc(sizeof(t_stats));
	if (ft_test_arguments(argc, argv) == 1 || !(stats))
		return (NULL);
	if (init_stats(argc, argv, stats) <= 0)
	{
		free(stats);
		return (NULL);
	}
	return (stats);
}

void	*check_if_alive(t_data **p)
{
	int	ch;
	int	i;

	ch = 0;
	while (1 == 1)
	{
		i = -1;
		while (++i < p[0]->stats->number_of_philo)
		{
			pthread_mutex_lock(&p[i]->stats->life);
			if (((ft_tempo() - p[i]->timer) > p[i]->stats->time_to_die && ch++))
			{
				console_info(p[i]->philo_nb, " died\n", p[i]->stats->write_fd_1, \
					p[i]->stats->program_timer);
				ch = 1;
			}
			pthread_mutex_unlock(&p[i]->stats->life);
			if (ch == 1)
				break ;
			usleep(10);
		}
		if (ch == 1)
			break ;
	}
	return (NULL);
}

void	norm_manage_threads(t_stats *stats, t_data	**philo)
{
	int	x;

	x = -1;
	stats->end_of_philo = 42;
	while (++x < stats->number_of_philo)
	{
		philo[x] = malloc(sizeof(t_data));
		a_philo_has_born(stats, philo, x);
	}
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

	stats = ft_return_stats(argc, argv);
	if (!(stats))
		return (1);
	philo = malloc(sizeof(t_data *) * stats->number_of_philo);
	if (!(philo))
	{
		free(stats);
		return (1);
	}
	norm_manage_threads(stats, philo);
	free(stats->fork);
	pthread_mutex_destroy(&stats->write_fd_1);
	free(philo);
	free(stats);
	return (1);
}

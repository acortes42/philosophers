/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 14:42:06 by acortes-          #+#    #+#             */
/*   Updated: 2022/04/09 12:17:21 by acortes-         ###   ########.fr       */
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

void	check_if_alive(t_data *philo, t_stats *stats)
{
	unsigned long long int	origin;
	unsigned long long int	die;

	die = stats->time_to_die;
	while (!check_if_end(&(*philo)))
	{
		pl_usleep(5);
		origin = pl_get_time_msec();
		pthread_mutex_lock(&stats->check_timer);
		if ((origin - philo[0].timer) > die)
		{
			pthread_mutex_unlock(&stats->check_timer);
			norminette_chech_if_alive(philo, 0);
			break ;
		}
		else if (philo->number_of_philo > 1 && (origin - philo[stats->number_of_philo - 2].timer) > die)
		{
			pthread_mutex_unlock(&stats->check_timer);
			norminette_chech_if_alive(philo, stats->number_of_philo - 2);
			break ;
		}
		else
			pthread_mutex_unlock(&stats->check_timer);
	}
}

void	init_philo(t_data *philo, t_stats *stats)
{
	int		x;

	x = -1;
	stats->all_to_eat = stats->number_of_philo;
	while (++x < stats->number_of_philo)
	{
		philo[x].philo_nb = x + 1;
		philo[x].nb_eat = 0;
		philo[x].stats = stats;
		philo[x].end_of_this_philo = 42;
		philo[x].number_of_philo = stats->number_of_philo;
		philo[x].time_to_die = stats->time_to_die;
		philo[x].time_eating = stats->time_eating;
		philo[x].time_sleeping = stats->time_sleeping;
		philo[x].times_eating = stats->times_eating;
	}
	x = -1;
	stats->tmp_int = 0;
	stats->program_timer = pl_get_time_msec();
}

void	aux_threads(t_stats *stats)
{
	int		x;
	t_data	*philo;

	philo = malloc(sizeof(t_data) * 200);
	init_philo(philo, stats);
	x = -1;
	while (++x < stats->number_of_philo)
		pthread_create(&philo[x].thread, NULL, &summon_a_philo, &philo[x]);
	check_if_alive(philo, stats);
	x = -1;
	while (++x < stats->number_of_philo)
		pthread_join(philo[x].thread, NULL);
	x = -1;
	while (++x < stats->number_of_philo)
		pthread_mutex_destroy(&stats->fork[x]);
	pthread_mutex_destroy(&stats->end_of_philo_mutex);
	pthread_mutex_destroy(&stats->tmp_int_mutex);
	pthread_mutex_destroy(&stats->all_to_eat_mutex);
	pthread_mutex_destroy(&stats->write_fd_1);
	pthread_mutex_destroy(&stats->check_timer);
	free(philo);
}

int	main(int argc, char **argv)
{
	t_stats	stats;
	int		tmp_int;

	tmp_int = ft_return_stats(argc, argv, &stats);
	if (!tmp_int)
		return (0);
	aux_threads(&stats);
	pthread_mutex_destroy(&stats.write_fd_1);
	free(stats.fork);
	return (1);
}

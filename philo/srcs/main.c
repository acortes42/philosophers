/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 14:42:06 by acortes-          #+#    #+#             */
/*   Updated: 2022/03/29 17:23:14 by acortes-         ###   ########.fr       */
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

/*
void	check_if_alive(t_data **philo, t_stats *stats)
{
	int		check;
	int		i;

	check = 0;
	while(check_if_start(&(*philo[0])))
		;
	while (!check_if_end(*philo))
	{
		i = -1;
		while (++i < philo[0]->number_of_philo && \
			!check_if_end(*philo))
		{
			usleep(50);
			pthread_mutex_lock(&stats->life);
			if (pl_get_time_msec() - philo->stats->program_timer > (long long unsigned int)stats->time_to_die)
			{
				console_info(philo[i]->philo_nb, "is sleeping\n", &(*philo[i]), 1);
				end_to_zero(&(*philo[0]));
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
*/

void	aux_threads(int argc, char **argv)
{
	int	x; 
	t_data	*philo;
	int		tmp_int;
	t_stats	stats;

	tmp_int = ft_return_stats(argc, argv, &stats);
	if (!tmp_int)
		return;
	x = -1;
	//pthread_mutex_lock(&stats.tmp_int_mutex);
	//stats.tmp_int = 0;
	philo = malloc(sizeof(t_data) * 250);
	stats.all_to_eat = stats.number_of_philo;
	while (++x < stats.number_of_philo)
	{
		philo[x].philo_nb = x + 1;
		philo[x].nb_eat = 0;
		philo[x].stats = &stats;
		philo[x].end_of_this_philo = 42;
		philo[x].number_of_philo = stats.number_of_philo;
		philo[x].time_to_die = stats.time_to_die;
		philo[x].time_eating = stats.time_eating;
		philo[x].time_sleeping = stats.time_sleeping;
		philo[x].times_eating = stats.times_eating;
	}
	x = -1;
	stats.program_timer = pl_get_time_msec();
	while (++x < stats.number_of_philo)
	{
		pthread_create(&philo[x].thread, NULL, &summon_a_philo, &philo[x]);
	}
	
	//change_tmp_int(&stats, 1);
	/*pthread_mutex_lock(&stats.tmp_int_mutex);
	stats.tmp_int = x;
	pthread_mutex_unlock(&stats.tmp_int_mutex);*/
	//check_if_alive(&philo, &stats);
	x = -1;
	while (++x < stats.number_of_philo)
		pthread_join(philo[x].thread, NULL);
	x = -1;
	while (++x < stats.number_of_philo)
		pthread_mutex_destroy(&stats.fork[x]);
	free(philo);
}

int	main(int argc, char **argv)
{
	t_stats	stats;
	int		tmp_int;

	tmp_int = ft_return_stats(argc, argv, &stats);
	if (!tmp_int)
		return(0);
	aux_threads(argc, argv);
	pthread_mutex_destroy(&stats.write_fd_1);
	free(stats.fork);
	return (1);
}

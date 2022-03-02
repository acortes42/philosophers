/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 14:54:52 by acortes-          #+#    #+#             */
/*   Updated: 2022/03/02 16:44:13 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	go_sleep(t_data *philo)
{
	printf(_BLUE);
	if (philo->end_of_this_philo != 0)
	{
		if (philo->stats->end_of_philo > 0)
			console_info(philo->philo_nb, "is sleeping\n", \
				philo->stats->write_fd_1, philo->stats->program_timer);
		if (philo->stats->time_to_die > philo->stats->time_sleeping)
			pl_usleep(philo->stats->time_sleeping);
		else
		{
			pl_usleep(philo->stats->time_to_die);
			philo->stats->end_of_philo = 0;
		}
	}
	return (1);
}

int	breathing(t_data *philo)
{
	if (philo->stats->end_of_philo > 0 && eat(philo) > 0)
	{
		if (go_sleep(philo) <= 0)
			return (-1);
		if (philo->end_of_this_philo != 0)
		{
			printf(_YELLOW);
			if (philo->stats->end_of_philo > 0)
				console_info(philo->philo_nb, "is thinking\n", \
					philo->stats->write_fd_1, philo->stats->program_timer);
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
	printf(_MAGENTA);
	philo->timer = ft_tempo();
	while (breathing((philo)) > 0)
		NULL;
	if (philo->stats->all_to_eat == 0)
	{
		philo->stats->end_of_philo = 0;
		if (philo)
			free(philo);
		return (NULL);
	}
	philo->stats->end_of_philo = 0;
	if (philo)
		free(philo);
	return (NULL);
}

int	a_philo_has_born(t_stats *stats, t_data **philo, int x)
{
	philo[x]->philo_nb = x + 1;
	philo[x]->nb_eat = 0;
	philo[x]->stats = stats;
	philo[x]->end_of_this_philo = 42;
	philo[x]->stats->all_to_eat = stats->number_of_philo;
	philo[x]->stats->value_lfork = x;
	philo[x]->stats->value_rfork = (x + 1) % stats->number_of_philo;
	return (1);
}

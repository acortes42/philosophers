/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 23:37:35 by adrian            #+#    #+#             */
/*   Updated: 2021/07/24 23:43:50 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
	stats->end_of_philo = 42;
	return (stats);
}

int	normi_die(t_data **philo, int i)
{
	printf(_RED);
	philo[i]->stats->end_of_philo = 0;
	console_info(philo[i]->philo_nb, " died\n", \
		philo[i]->stats->write_fd_1, philo[i]->stats->program_timer);
	return (1);
}

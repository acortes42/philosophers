/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 14:42:06 by acortes-          #+#    #+#             */
/*   Updated: 2021/05/09 17:18:26 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int				ft_change_to_int(char *str, long *nb)
{
	if (*str == '\0')
		return (-1);
    if (ft_strlen(str) > 7)
    {
        printf(_RED"Is this a buffer overflow?\n");
        return (-1);
    }
	*nb = 0;
	while (*str && *str >= '0' && *str <= '9')
		*nb = 10 * *nb + (*str++ - '0');
	if (*str != '\0')
		return (-1);
	return (0);
}

int init_stats(int argc, char **argv, s_stats *stats)
{
    int     x;

    x = 0;
    if (argc < 4)
        return (0);
    if (ft_change_to_int(argv[1], (long *)&stats->number_of_philo) == -1 || 
        ft_change_to_int(argv[2], &stats->time_to_die) == -1 || ft_change_to_int(argv[3], &stats->time_eating) || 
        ft_change_to_int(argv[4], &stats->time_sleeping))
        return (0);

    stats->timer = ft_tempo();
    if (!(stats->fork = malloc(sizeof(pthread_mutex_t) * stats->number_of_philo)))
        return (-1);
    if (argv[5])
        ft_change_to_int(argv[5],(long *)&stats->times_eating);
    else
        stats->times_eating = -1;
    
    while (x < stats->number_of_philo)
    {
        pthread_mutex_init(&stats->fork[x], NULL);
        stats->value_lfork = x;
        stats->value_rfork = (x + 1) % stats->number_of_philo;
        x++;
    }
    pthread_mutex_init(&stats->write_fd_1 , NULL);

    return (1);
}

int ft_process_argv(char **argv)
{
    long    x;

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

int ft_test_arguments(int argc, char **argv)
{
    long    x;

    x = 0;
    if ((argc != 5 && argc != 6) || ft_process_argv(argv) == 1)
    {
        printf("Incorrect arguments\n");
        return (1);
    }
    if (ft_change_to_int(argv[1], &x) < 0)
        return (1);
    if (x < 1)
    {
        printf("No existence == No death\n");
        return (1);
    }
    if (x == 1)
    {
        printf("Our philosopher only have one fork. Instakill.\n");
        return (1);
    }
    return (0);
}

int     main(int argc, char **argv)
{
    s_stats         *stats;
    s_data          **philo;
    int             x;

    x  = 0;
    if (ft_test_arguments(argc, argv) == 1)
        return (1);
    if (!(stats = malloc(sizeof(s_stats))))
        return (1);
    if (init_stats(argc, argv, stats) <= 0)
    {
        free(stats);
        return (1);
    }
    if (!(philo = malloc(sizeof(s_data *) * stats->number_of_philo)))
    {
        free(stats);
        return (1);
    }
    stats->end_of_philo = 42;
    while (x < stats->number_of_philo)
    {
        philo[x] = malloc(sizeof(s_data));
        a_philo_has_born(stats, philo, x);
        x++;
    }
    while (stats->end_of_philo > 0) 
        ;
    x = 0;
    while (x < stats->number_of_philo)
    {
        pthread_join(philo[x]->thread, NULL);
        x++;
    }
    msg_write("END\n");
    x = 0;
    ft_free_all(*philo);
    if (philo)
        free(philo);
    if (stats)
        free(stats);
    return (1);
}

/*
    Igual debo hacer algo con lo que se pierde en multihilo. Que sinceramente no se donde se va. (Y creo que provoca uno
        o dos leaks)
*/
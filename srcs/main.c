/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 14:42:06 by acortes-          #+#    #+#             */
/*   Updated: 2021/05/20 22:28:38 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int ft_change_to_int(char *str, long *nb)
{
    int x;
    
    x = ft_strlen(str);
    if (*str == '\0')
        return (-1);
    if (x > 7)
    {
        printf(_RED"Hey, use lower numbers\n");
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
    int x;
    
    x = 0;
    if (argc < 4)
        return (0);
    if (ft_change_to_int(argv[1], (long *)&stats->number_of_philo) == -1 ||
        ft_change_to_int(argv[2], &stats->time_to_die) == -1 ||
        ft_change_to_int(argv[3], &stats->time_eating) ||
        ft_change_to_int(argv[4], &stats->time_sleeping))
        return (0);
    if (stats->number_of_philo > 500)
    {
        printf("The max number the philosophers is 500\n");
        return (0);
    }
    if (!(stats->fork = malloc(sizeof(pthread_mutex_t) * stats->number_of_philo)))
        return (-1);
    if (argv[5])
    {
        if (ft_change_to_int(argv[5],(long *)&stats->times_eating) == -1)
            return (0);
    }
    else
        stats->times_eating = -1;
    
    while (x < stats->number_of_philo)
    {
        pthread_mutex_init(&stats->fork[x], NULL);
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

s_stats *ft_return_stats(int argc, char **argv)
{
    s_stats         *stats;
    int             x;

    x  = -1;
    stats = malloc(sizeof(s_stats));
    if (ft_test_arguments(argc, argv) == 1 || !(stats))
        return (NULL);
    if (init_stats(argc, argv, stats) <= 0)
    {
        free(stats);
        return (NULL);
    }
    return (stats);
}

void *check_if_alive(s_data **philo)
{
    int     check;

    check = 0;
    while (1 == 1)
    {
        for (int i = 0; i < philo[0]->stats->number_of_philo;i++)
        {
            pthread_mutex_lock(&philo[i]->stats->life);
            if (((ft_tempo() - philo[i]->timer) > philo[i]->stats->time_to_die))
            {
                printf(_RED);
                pthread_mutex_unlock(&philo[i]->stats->life);
                philo[i]->stats->end_of_philo = 0;
                check = 1;
                console_info(philo[i]->philo_nb, " died\n", philo[i]->stats->write_fd_1, philo[i]->stats->program_timer);
            }
            pthread_mutex_unlock(&philo[i]->stats->life);
            if (check == 1)
                break;
            usleep(100);
        }
        if (check == 1)
            break;
    }
    return (NULL);
}

int     main(int argc, char **argv)
{
    s_stats         *stats;
    s_data          **philo;
    int             x;

    x  = -1;
    stats = ft_return_stats(argc, argv);
    if (!(stats))
        return (1);
    philo = malloc(sizeof(s_data *) * stats->number_of_philo);
    if (!(philo))
    {
        free(stats);
        return (1);
    }
    stats->end_of_philo = 42;
    while (++x < stats->number_of_philo)
    {
        philo[x] = malloc(sizeof(s_data));
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
 //   msg_write("END\n");
    x = -1;
	while (++x < stats->number_of_philo)
		pthread_mutex_destroy(&stats->fork[x]);
	free(stats->fork);
	pthread_mutex_destroy(&stats->write_fd_1);
    free(philo);
    free(stats);
    return (1);
}

/*
    Hay bastantes leaks a tratar
*/
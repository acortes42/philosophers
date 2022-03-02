/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:59:29 by adrian            #+#    #+#             */
/*   Updated: 2021/07/25 00:21:51 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

# define _RED     "\x1b[31m"
# define _GREEN   "\x1b[32m"
# define _YELLOW  "\x1b[33m"
# define _BLUE    "\x1b[34m"
# define _MAGENTA "\x1b[35m"
# define _CYAN    "\x1b[36m"
# define _RESET   "\x1b[0m"

typedef struct s_stats
{
	int				number_of_philo;
	long			time_to_die;
	long			time_eating;
	long			time_sleeping;
	int				times_eating;
	int				end_of_philo;
	int				value_lfork;
	int				value_rfork;
	int				program_timer;
	pthread_mutex_t	*fork;
	pthread_mutex_t	life;
	pthread_mutex_t	write_fd_1;
}	t_stats;

typedef struct s_data
{
	int			philo_nb;
	int			nb_eat;
	int			timer;
	pthread_t	thread;
	t_stats		*stats;
}	t_data;

typedef struct s_philo
{
	t_stats	stats;
	t_data	data;

}	t_philo;

int		eat(t_data *philo);
int		init_stats(int argc, char **argv, t_stats *stats);
int		to_int(char *str, long *nb);
int		breathing(t_data *philo);
void	console_info(int x, char *str, pthread_mutex_t mutex, int timer);
int		eat(t_data *philo);
int		a_philo_has_born(t_stats *stats, t_data **philo, int x);
void	ft_putnbr_fd(int n, int fd);
int		free_philo(t_data **philo, t_stats *stats);
int		now_vs_old_time(struct timeval old);
int		ft_tempo(void);
void	*summon_a_philo(void *args);
size_t	ft_strlen(const char *s);
int		ft_test_arguments(int argc, char **argv);
int		ft_process_argv(char **argv);
t_stats	*ft_return_stats(int argc, char **argv);
int		normi_die(t_data **philo, int i);
void	free_stats(t_stats *stats);

#endif

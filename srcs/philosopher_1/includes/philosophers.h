#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>


typedef struct      t_stats
{
    int             number_of_philo;
    unsigned long   time_to_die;
    unsigned long   time_eating;
    unsigned long   time_sleeping;
    int             times_eating;
    struct timeval  *time_start;
    pthread_mutex_t **left;
    pthread_mutex_t **right;
}                   s_stats;

typedef struct      t_data
{
    int             philo_nb;
    int             nb_eat;
    pthread_t       *thread;
    struct timeval  *last_meat;
    s_stats         *stats;
    void            *next;
}                   s_data;

typedef struct      t_philo
{
    s_stats         stats;
    s_data          data;

}                   s_philo;

void	msg_write(char *msg);
void    console_info(int x, char *str);
int     eat(s_data *philo);
int     a_philo_has_born (s_stats *stats);
void	ft_putnbr_fd(int n, int fd);
int     free_stats(s_stats *stats);
#endif
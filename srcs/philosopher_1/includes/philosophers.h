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

typedef struct      t_stats
{
    int             number_of_philo;
    long            time_to_die;
    long            time_eating;
    long            time_sleeping;
    int             times_eating;
    int             end_of_philo;
    int             value_lfork;
    int             value_rfork;
    int             timer;
    pthread_mutex_t *fork;
    //  pthread_mutex_t *eating;  Puede que tenga que usarlo para la lógica del ejercicio.
    pthread_mutex_t write_fd_1;
    }                   s_stats;

typedef struct      t_data
{
    int             philo_nb;
    int             nb_eat;
    int             program_timer;
    pthread_t       thread;
    s_stats         *stats;
}                   s_data;

typedef struct      t_philo
{
    s_stats         stats;
    s_data          data;

}                   s_philo;

void	msg_write(char *msg);
void    console_info(int x, char *str, pthread_mutex_t mutex, int timer);
int     eat(s_data *philo);
int     a_philo_has_born (s_stats *stats, s_data **philo, int x);
void	ft_putnbr_fd(int n, int fd);
int     free_philo(s_data **philo, s_stats *stats);
int     now_vs_old_time(struct timeval old);
int		ft_tempo();
void    *summon_a_philo(void *args);
size_t	ft_strlen(const char *s);

#endif
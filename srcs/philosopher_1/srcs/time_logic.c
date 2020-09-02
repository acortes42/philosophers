#include "../includes/philosophers.h"

int now_vs_old_time(struct timeval old)
{
    int             x;
    int				y;
	struct timeval	now;

    gettimeofday(&now, NULL);
	x = (now.tv_sec - old.tv_sec) / 10;
	if (now.tv_usec >= old.tv_sec)
		y = ((now.tv_usec - old.tv_sec)) / 1000;
	else
	{
		if (x > 0)
			x--;
		y = ((old.tv_sec - now.tv_usec)) / 1000;
	}
    	ft_putnbr_fd(x, 1);
    	msg_write("\n");
	    ft_putnbr_fd((x * 1000 + y * 0.001), 1);
    	msg_write("\n");
    return (x * 1000 + y * 0.001);
}


int	ask_if_alive(s_data *philo)
{
    if (now_vs_old_time(philo->last_meat) > philo->stats->time_to_die)
        return (-1);
	else
		return(1);
}

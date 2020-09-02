#include "../includes/philosophers.h"

    //mensaje temporal a falta de elaborado
size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}

void	ft_putnbr_fd(int n, int fd)
{
	int x;

	x = 0;
	if (n == -2147483648)
	{
		write(fd, "-", 1);
		write(fd, "2147483648", 10);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(n * (-1), fd);
	}
	else
	{
		if (n >= 10)
			ft_putnbr_fd((n / 10), fd);
		x = (n % 10) + '0';
		write(fd, &x, 1);
	}
}

void	msg_write(char *msg)
{
	write(1, msg, ft_strlen(msg));
}

void    console_info(int x, char *str)
{
 	struct timeval now;

    gettimeofday(&now, NULL); 
    ft_putnbr_fd((now.tv_sec + now.tv_usec * 0.001), 1);
    msg_write("	");
    ft_putnbr_fd(x, 1);
    msg_write("	");
    msg_write(str);
}


// error en el calculo

int	ask_if_alive(s_data *philo)
{
	time_t			x;
	int				y;
	struct timeval	now;

    gettimeofday(&now, NULL);
	x = (now.tv_sec - philo->last_meat.tv_sec) / 10;
	if (now.tv_usec >= philo->last_meat.tv_sec)
		y = ((now.tv_usec - philo->last_meat.tv_sec)) / 1000;
	else
	{
		if (x > 0)
			x--;
		y = ((philo->last_meat.tv_sec - now.tv_usec)) / 1000;
	}
		ft_putnbr_fd(x, 1);
    	msg_write("\n");
	    ft_putnbr_fd((x * 1000 + y * 0.001), 1);
    	msg_write("\n");
    if ((x * 1000 + y * 0.001) > philo->stats->time_to_die)
        return (-1);
	else
		return(1);
}

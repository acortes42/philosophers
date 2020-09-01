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

//segfault por aqui, seguramente en uso de ese itoa

void    console_info(int x, char *str)
{
 	struct timeval now;

    gettimeofday(&now, NULL); 
    ft_putnbr_fd((now.tv_sec + now.tv_usec * 0.001), 1);
    msg_write(" ");
    ft_putnbr_fd(x, 1);
    msg_write(" ");
    msg_write(str);
  //  free(now);
}

int	free_stats(s_stats *stats)
{
	int	x;

	x = 0;
	while (x < stats->number_of_philo)
	{
		free(stats->left[x]);
		free(stats->right[x]);
		x++;
	}
	free(stats->left);
	free(stats->right);
	free(stats);
	return (1);
}


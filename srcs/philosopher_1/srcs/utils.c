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

void    console_info(int x, char *str, pthread_mutex_t mutex)
{
 	struct timeval now;

	pthread_mutex_lock(&mutex);
    gettimeofday(&now, NULL); 
	printf("%ld", now.tv_sec); 
	printf("%ld %d %s", (long int)(/*now.tv_sec * 1000 + */now.tv_usec * 0.001), x, str);
	usleep(100);
    /*msg_write(" ");
    ft_putnbr_fd(x, 1);
	usleep(100);
    msg_write(" ");
    msg_write(str);*/
	pthread_mutex_unlock(&mutex);
}

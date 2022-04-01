/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 14:54:26 by acortes-          #+#    #+#             */
/*   Updated: 2022/04/01 14:52:04 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
	int	x;

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

void	console_info(int x, char *str, t_data *philo, int last_breath)
{
	(void) last_breath;
	pthread_mutex_lock(&philo->stats->write_fd_1);
	if (!check_if_end(&(*philo)))
		printf("%lld %d %s", pl_get_time_msec() - \
			philo->stats->program_timer, x, str);
	pthread_mutex_unlock(&philo->stats->write_fd_1);
}

#include "../includes/philosophers.h"

// esto es legacy. Se puede sustituir por una función que nos 

int		ft_tempo()
{
	struct timeval	tv;
	int				i;

	gettimeofday(&tv, NULL);
	i = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:23:19 by dsatge            #+#    #+#             */
/*   Updated: 2025/05/05 15:14:32 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_putstrfd(char *str, int fd)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	return ;
}

long long int	get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long long int t_ms, t_data *data)
{
	long long int	curr_time;

	curr_time = get_time_ms();
	while ((get_time_ms() - curr_time) < t_ms)
	{
		pthread_mutex_lock(&data->mutex_stop);
		if (data->stop == 1)
		{
			pthread_mutex_unlock(&data->mutex_stop);
			break ;
		}
		pthread_mutex_unlock(&data->mutex_stop);
		if (t_ms > 10000000)
			usleep(t_ms / 100000);
		else
			usleep(t_ms / 10);
	}
}

void	printf_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->mutex_stop);
	if (philo->data->stop == 1 || feededphilo_check(philo->data) == 1)
	{
		pthread_mutex_unlock(&philo->data->mutex_stop);
		return ;
	}
	pthread_mutex_unlock(&philo->data->mutex_stop);
	pthread_mutex_lock(&philo->data->mutex_msg);
	printf("%09lld %i %s", (get_time_ms() - philo->data->start_time),
		philo->id, str);
	pthread_mutex_unlock(&philo->data->mutex_msg);
}

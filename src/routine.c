/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:22:33 by dsatge            #+#    #+#             */
/*   Updated: 2025/05/05 14:58:07 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	eat_odd(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo->leftfork);
	printf_status(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->rightfork);
	printf_status(philo, "has taken a fork\n");
	pthread_mutex_lock(&philo->data->mutex_stop);
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(philo->leftfork);
		pthread_mutex_unlock(philo->rightfork);
		pthread_mutex_unlock(&philo->data->mutex_stop);
		return ;
	}
	pthread_mutex_unlock(&philo->data->mutex_stop);
	printf_status(philo, "is eating\n");
	pthread_mutex_lock(&philo->data->mutex_lastmeal);
	philo->lastmeal = get_time_ms();
	pthread_mutex_unlock(&philo->data->mutex_lastmeal);
	pthread_mutex_lock(&philo->data->mutex_countmeal);
	if (philo->data->stop == 0)
		philo->count_meal++;
	pthread_mutex_unlock(&philo->data->mutex_countmeal);
	ft_usleep(philo->data->time_to_eat, data);
	pthread_mutex_unlock(philo->leftfork);
	pthread_mutex_unlock(philo->rightfork);
}

static void	eat_even(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo->leftfork);
	printf_status(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->rightfork);
	printf_status(philo, "has taken a fork\n");
	pthread_mutex_lock(&philo->data->mutex_stop);
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(philo->leftfork);
		pthread_mutex_unlock(philo->rightfork);
		pthread_mutex_unlock(&philo->data->mutex_stop);
		return ;
	}
	pthread_mutex_unlock(&philo->data->mutex_stop);
	printf_status(philo, "is eating\n");
	pthread_mutex_lock(&philo->data->mutex_lastmeal);
	philo->lastmeal = get_time_ms();
	pthread_mutex_unlock(&philo->data->mutex_lastmeal);
	pthread_mutex_lock(&philo->data->mutex_countmeal);
	if (philo->data->stop == 0)
		philo->count_meal++;
	pthread_mutex_unlock(&philo->data->mutex_countmeal);
	ft_usleep(philo->data->time_to_eat, data);
	pthread_mutex_unlock(philo->rightfork);
	pthread_mutex_unlock(philo->leftfork);
}

void	eat(t_philo *philo, t_data *data)
{
	if (data->philo_nbr % 2 == 0)
		eat_even(philo, data);
	else
		eat_odd(philo, data);
}

int	sleep_f(t_philo *philo, t_data *data)
{
	if (death_check(philo->data) == 1)
		return (stop_routine(philo), 0);
	printf_status(philo, "is sleeping\n");
	ft_usleep(philo->data->time_to_sleep, data);
	return (1);
}

int	think(t_philo *philo, t_data *data)
{
	if (death_check(philo->data) == 1)
		return (stop_routine(philo), 0);
	printf_status(philo, "is thinking\n");
	if (philo->data->philo_nbr % 2 != 0)
		ft_usleep(philo->data->time_to_eat / 10, data);
	return (1);
}

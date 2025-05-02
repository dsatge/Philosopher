/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:22:33 by dsatge            #+#    #+#             */
/*   Updated: 2025/05/02 16:23:07 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eat(t_philo *philo, t_general *general)
{
	pthread_mutex_lock(philo->leftfork);
	printf_status(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->rightfork);
	printf_status(philo, "has taken a fork\n");
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(philo->leftfork);
		pthread_mutex_unlock(philo->rightfork);
		return ;
	}
	printf_status(philo, "is eating\n");
	pthread_mutex_lock(&philo->data->mutex_lastmeal);
	philo->lastmeal = get_time_ms();
	pthread_mutex_unlock(&philo->data->mutex_lastmeal);
	pthread_mutex_lock(&philo->data->mutex_eat);
	if (philo->data->stop == 0)
		philo->data->meals_count++;
	pthread_mutex_unlock(&philo->data->mutex_eat);
	ft_usleep(philo->data->time_to_eat, general);
	pthread_mutex_unlock(philo->leftfork);
	pthread_mutex_unlock(philo->rightfork);
}

int	sleep_f(t_philo *philo, t_general *general)
{
	if (death_check(philo->data) == 1)
		return (stop_routine(philo), 0);
	printf_status(philo, "is sleeping\n");
	ft_usleep(philo->data->time_to_sleep, general);
	return (1);
}

int	think(t_philo *philo, t_general *general)
{
	if (death_check(philo->data) == 1)
		return (stop_routine(philo), 0);
	printf_status(philo, "is thinking\n");
	if (philo->data->philo_nbr % 2 != 0)
		ft_usleep(philo->data->time_to_eat / 10, general);
	return (1);
}

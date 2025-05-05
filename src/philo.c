/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:22:20 by dsatge            #+#    #+#             */
/*   Updated: 2025/05/05 15:06:37 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	death_check(t_data *data)
{
	int	exit_status;

	exit_status = 0;
	pthread_mutex_lock(&data->mutex_stop);
	if (data->stop == 1)
		exit_status = 1;
	pthread_mutex_unlock(&data->mutex_stop);
	return (exit_status);
}

int	feededphilo_check(t_data *data)
{
	int	i;
	int	feed_status;

	i = 0;
	feed_status = 0;
	pthread_mutex_lock(&data->mutex_countmeal);
	if (data->meals_count == 0)
	{
		pthread_mutex_unlock(&data->mutex_countmeal);
		return (0);
	}
	pthread_mutex_unlock(&data->mutex_countmeal);
	while (i < data->philo_nbr)
	{
		pthread_mutex_lock(&data->mutex_countmeal);
		if (data->philo[i].count_meal >= data->meals_count)
			feed_status++;
		pthread_mutex_unlock(&data->mutex_countmeal);
		i++;
	}
	if (feed_status >= data->philo_nbr)
		return (stop_routine(data->philo), 1);
	return (0);
}

void	*philo_routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	pthread_mutex_lock(&philo->data->mutex_lastmeal);
	philo->lastmeal = philo->data->start_time;
	pthread_mutex_unlock(&philo->data->mutex_lastmeal);
	if (philo->data->philo_nbr == 1)
	{
		ft_usleep(philo->data->time_to_die + 10, philo->data);
		return (stop_routine(philo));
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 10, philo->data);
	while (death_check(philo->data) == 0)
	{
		eat(philo, philo->data);
		sleep_f(philo, philo->data);
		think(philo, philo->data);
	}
	return (stop_routine(philo));
}

int	philo_launch(t_data *data)
{
	int			i;

	i = 0;
	data->start_time = get_time_ms();
	while (i < data->philo_nbr)
	{
		data->philo[i].lastmeal = data->start_time;
		if (pthread_create(&data->philo[i].thread,
				NULL, &philo_routine, &data->philo[i]) != 0)
			return (ft_exit(data, data->philo, 4, i));
		i++;
	}
	pthread_create(&data->thread_death, NULL, &last_meal, data);
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (1);
		i++;
	}
	if (pthread_join(data->thread_death, NULL))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   survive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:23:05 by dsatge            #+#    #+#             */
/*   Updated: 2025/05/03 17:19:12 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_mealsreach(t_data *data)
{
	int	i;
	int	eaten_meals;

	i = 0;
	eaten_meals = 0;
	if (data->meals_count == 0)
		return (1);
	while (i < data->philo_nbr)
	{
		pthread_mutex_lock(&data->mutex_eat);
		if (data->philo[i].count_meal >= data->meals_count)
			eaten_meals++;
		pthread_mutex_unlock(&data->mutex_eat);
		i++;
	}
	if (eaten_meals == data->philo_nbr)
	{
		pthread_mutex_lock(&data->mutex_msg);
		printf("%09lld all philosophers had %d meals\n",
			(get_time_ms() - data->start_time),
			data->meals_count);
		pthread_mutex_unlock(&data->mutex_msg);
		return (0);
	}
	return (1);
}

void	starvation_death(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->data->mutex_stop);
	philo->data->stop = 1;
	pthread_mutex_unlock(&philo->data->mutex_stop);
	pthread_mutex_lock(&philo->data->mutex_msg);
	ft_usleep(philo->data->time_to_eat / 10, data);
	printf("%09lld %d %s", get_time_ms() - philo->data->start_time, \
		philo->id, "died\n");
	pthread_mutex_unlock(&philo->data->mutex_msg);
}

void	*last_meal(void *v_data)
{
	t_data	*data;
	int			i;

	data = (t_data *)v_data;
	while (data->stop == 0)
	{
		i = 0;
		while (i < data->philo_nbr)
		{
			pthread_mutex_lock(&data->mutex_lastmeal);
			if ((get_time_ms() - data->philo[i].lastmeal)
				>= data->time_to_die)
			{
				starvation_death(&data->philo[i], data);
				pthread_mutex_unlock(&data->mutex_lastmeal);
				return (NULL);
			}
			pthread_mutex_unlock(&data->mutex_lastmeal);
			i++;
		}
		if (check_mealsreach(data) == 0)
			return (NULL);
		ft_usleep(data->time_to_eat / 10, data);
	}
	return (NULL);
}

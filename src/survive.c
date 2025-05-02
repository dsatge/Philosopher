/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   survive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:23:05 by dsatge            #+#    #+#             */
/*   Updated: 2025/05/02 16:47:42 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_mealsreach(t_general *general)
{
	int	i;
	int	eaten_meals;

	i = 0;
	eaten_meals = 0;
	if (general->data.meals_count == 0)
		return (1);
	while (i < general->data.philo_nbr)
	{
		pthread_mutex_lock(&general->data.mutex_eat);
		if (general->philo[i].count_meal >= general->data.meals_count)
			eaten_meals++;
		pthread_mutex_unlock(&general->data.mutex_eat);
		i++;
	}
	if (eaten_meals == general->data.philo_nbr)
	{
		pthread_mutex_lock(&general->data.mutex_msg);
		printf("%09lld all philosophers had %d meals\n",
			(get_time_ms() - general->data.start_time),
			general->data.meals_count);
		pthread_mutex_unlock(&general->data.mutex_msg);
		return (0);
	}
	return (1);
}

void	starvation_death(t_philo *philo, t_general *general)
{
	pthread_mutex_lock(&philo->data->mutex_stop);
	philo->data->stop = 1;
	pthread_mutex_unlock(&philo->data->mutex_stop);
	pthread_mutex_lock(&philo->data->mutex_msg);
	ft_usleep(philo->data->time_to_eat / 10, general);
	printf("%09lld %d %s", get_time_ms() - philo->data->start_time, \
		philo->id, "died\n");
	pthread_mutex_unlock(&philo->data->mutex_msg);
}

void	*last_meal(void *v_general)
{
	t_general	*general;
	int			i;

	general = (t_general *)v_general;
	while (general->data.stop == 0)
	{
		i = 0;
		while (i < general->data.philo_nbr)
		{
			pthread_mutex_lock(&general->data.mutex_lastmeal);
			if ((get_time_ms() - general->philo[i].lastmeal)
				>= general->data.time_to_die)
			{
				starvation_death(&general->philo[i], general);
				pthread_mutex_unlock(&general->data.mutex_lastmeal);
				return (NULL);
			}
			pthread_mutex_unlock(&general->data.mutex_lastmeal);
			i++;
		}
		if (check_mealsreach(general) == 0)
			return (NULL);
		ft_usleep(general->data.time_to_eat / 10, general);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   survive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:23:05 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/29 16:33:16 by dsatge           ###   ########.fr       */
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
		if (general->philo[i].meals_nbr >= general->data.meals_count)
			eaten_meals++;
		pthread_mutex_unlock(&general->data.mutex_eat);
		i++;
	}
	if (eaten_meals == general->data.philo_nbr)
	{
		pthread_mutex_lock(&general->data.mutex_console);
		printf("%09lld all philosophers had %d meals\n",
			(get_time_ms() - general->data.start_time),
			general->data.meals_count);
		pthread_mutex_unlock(&general->data.mutex_console);
		return (0);
	}
	return (1);
}

void	starvation_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_stop);
	philo->data->stop = 1;
	pthread_mutex_unlock(&philo->data->mutex_stop);
	pthread_mutex_lock(&philo->data->mutex_console);
	printf("%09lld %d %s", get_time_ms() - philo->data->start_time, \
		philo->id, "died\n");
	pthread_mutex_unlock(&philo->data->mutex_console);
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
			pthread_mutex_lock(&general->philo[i].mutex_t_meal);
			if ((get_time_ms() - general->philo[i].eating_t)
				>= general->data.time_to_die)
			{
				starvation_death(&general->philo[i]);
				pthread_mutex_unlock(&general->philo[i].mutex_t_meal);
				return (NULL);
			}
			pthread_mutex_unlock(&general->philo[i].mutex_t_meal);
			i++;
		}
		if (check_mealsreach(general) == 0)
			return (NULL);
	}
	return (NULL);
}

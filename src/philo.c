/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:22:20 by dsatge            #+#    #+#             */
/*   Updated: 2025/05/01 20:11:31 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*stop_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_stop);
	philo->data->stop = 1;
	pthread_mutex_unlock(&philo->data->mutex_stop);
	pthread_mutex_lock(&philo->data->mutex_msg);
	pthread_mutex_lock(&philo->data->mutex_msg);	
	return (NULL);
}

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

int	feededphilo_check(t_general *general)
{
	int	i;
	int	feed_status;

	i = 0;
	feed_status = 0;
	if (general->data.meals_count == 0)
		return (0);
	while (i < general->data.philo_nbr)
	{
		pthread_mutex_lock(&general->data.mutex_eat);
		if (general->philo[i].meals_nbr >= general->data.meals_count)
			feed_status++;
		pthread_mutex_unlock(&general->data.mutex_eat);
		i++;
	}
	if (feed_status >= general->data.philo_nbr)
		return (1);
	return (0);
}

void	*philo_routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 10, philo->data->general);
	while (death_check(philo->data) == 0)
	{
		eat(philo);
		sleep_f(philo);
		think(philo);
	}
	return (stop_routine(philo));
}

int	philo_launch(t_general *general)
{
	int			i;

	i = 0;
	while (i < general->data.philo_nbr)
	{
		if (pthread_create(&general->philo[i].thread,
				NULL, philo_routine, &general->philo[i]) != 0)
			return (ft_exit(general, general->philo, 5, i));
		i++;
	}
	pthread_create(general->data.thread_death, NULL, last_meal, general);
	pthread_join(general->data.thread_death, NULL);
	return (0);
}

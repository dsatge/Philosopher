/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:22:47 by dsatge            #+#    #+#             */
/*   Updated: 2025/05/05 15:15:47 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	initdata_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->mutex_msg, NULL))
		return (ft_putstrfd(ERR_INIT_MUTEX, 2), EXIT_FAILURE);
	if (pthread_mutex_init(&data->mutex_lastmeal, NULL))
		return (pthread_mutex_destroy(&data->mutex_msg),
			ft_putstrfd(ERR_INIT_MUTEX, 2), EXIT_FAILURE);
	if (pthread_mutex_init(&data->mutex_stop, NULL))
		return (pthread_mutex_destroy(&data->mutex_msg),
			pthread_mutex_destroy(&data->mutex_lastmeal),
			ft_putstrfd(ERR_INIT_MUTEX, 2), EXIT_FAILURE);
	if (pthread_mutex_init(&data->mutex_countmeal, NULL))
		return (pthread_mutex_destroy(&data->mutex_msg),
			pthread_mutex_destroy(&data->mutex_lastmeal),
			pthread_mutex_destroy(&data->mutex_stop),
			ft_putstrfd(ERR_INIT_MUTEX, 2), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	initforks_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->mutex_fork = malloc(sizeof(pthread_mutex_t *) * data->philo_nbr);
	if (!data->mutex_fork)
		return (ft_putstrfd(ERR_MALLOC_F, 2), EXIT_FAILURE);
	while (i < data->philo_nbr)
	{
		data->mutex_fork[i] = malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(data->mutex_fork[i], NULL))
			return (ft_putstrfd(ERR_INIT_MUTEX, 2), ft_dell_forks(data, i));
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	initphilo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philo)
		return (EXIT_FAILURE);
	memset(data->philo, 0, sizeof(t_philo) * data->philo_nbr);
	while (i < data->philo_nbr)
	{
		data->philo[i].id = (i + 1);
		data->philo[i].stop = 0;
		data->philo[i].data = data;
		data->philo[i].count_meal = 0;
		assign_forks(data, i);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init(t_data *data, int argc, char **argv)
{
	if (initdata_checkargs(data, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (initdata_mutex(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (initforks_mutex(data) == EXIT_FAILURE)
		return (free(data->philo), EXIT_FAILURE);
	if (initphilo(data) == EXIT_FAILURE)
		return (ft_exit(data, data->philo, 4, data->philo_nbr),
			EXIT_FAILURE);
	data->start_time = get_time_ms();
	return (0);
}

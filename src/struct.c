/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:22:47 by dsatge            #+#    #+#             */
/*   Updated: 2025/05/03 16:39:11 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	initdata_checkargs(t_data *data, int argc, char **argv)
{
	data->philo_nbr = convert_nbr(argv[1]);
	data->time_to_die = convert_nbr(argv[2]);
	data->time_to_eat = convert_nbr(argv[3]);
	data->time_to_sleep = convert_nbr(argv[4]);
	if (argc == 6)
		data->meals_count = convert_nbr(argv[5]);
	else
		data->meals_count = 0;
	if (check_parsing(data, argc) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_data(data, argc) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	data->stop = 0;
	data->start_time = -1;
	return (EXIT_SUCCESS);
}

static int	initdata_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->mutex_msg, NULL))
		return (ft_putstrfd(ERR_INIT_MUTEX, 2), EXIT_FAILURE);
	if (pthread_mutex_init(&data->mutex_eat, NULL))
		return (pthread_mutex_destroy(&data->mutex_msg)
			, ft_putstrfd(ERR_INIT_MUTEX, 2), EXIT_FAILURE);
	if (pthread_mutex_init(&data->mutex_lastmeal, NULL))
		return (pthread_mutex_destroy(&data->mutex_msg),
			pthread_mutex_destroy(&data->mutex_eat)
			, ft_putstrfd(ERR_INIT_MUTEX, 2), EXIT_FAILURE);
	if (pthread_mutex_init(&data->mutex_stop, NULL))
		return (pthread_mutex_destroy(&data->mutex_msg),
		pthread_mutex_destroy(&data->mutex_eat),
		pthread_mutex_destroy(&data->mutex_lastmeal),
		ft_putstrfd(ERR_INIT_MUTEX, 2), EXIT_FAILURE);
	if (pthread_mutex_init(&data->mutex_countmeal, NULL))
		return (pthread_mutex_destroy(&data->mutex_msg),
		pthread_mutex_destroy(&data->mutex_eat),
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

int	initphilo(t_data *data)
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
		if (data->philo_nbr % 2 == 0)
		{
			data->philo[i].leftfork = data->mutex_fork[i];
			data->philo[i].rightfork = data->mutex_fork[(i + 1)
				% data->philo_nbr];
		}
		else
		{
			data->philo[i].leftfork = data->mutex_fork[(i + 1)
				% data->philo_nbr];
			data->philo[i].rightfork = data->mutex_fork[i];
		}
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
		return (ft_exit(data, data->philo, 5, data->philo_nbr),
			EXIT_FAILURE);
	data->start_time = get_time_ms();
	return (0);
}

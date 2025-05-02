/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:22:47 by dsatge            #+#    #+#             */
/*   Updated: 2025/05/02 18:33:17 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	initdata_checkargs(t_general *general, int argc, char **argv)
{
	general->data.philo_nbr = convert_nbr(argv[1]);
	general->data.time_to_die = convert_nbr(argv[2]);
	general->data.time_to_eat = convert_nbr(argv[3]);
	general->data.time_to_sleep = convert_nbr(argv[4]);
	if (argc == 6)
		general->data.meals_count = convert_nbr(argv[5]);
	else
		general->data.meals_count = 0;
	if (check_parsing(general, argc) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_data(general, argc) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	general->data.stop = 0;
	general->data.start_time = -1;
	// general->data.general = general;
	return (EXIT_SUCCESS);
}

static int	initdata_mutex(t_general *general)
{
	if (pthread_mutex_init(&general->data.mutex_msg, NULL))
		return (ft_putstrfd(ERR_INIT_MUTEX, 2), EXIT_FAILURE);
	if (pthread_mutex_init(&general->data.mutex_eat, NULL))
		return (pthread_mutex_destroy(&general->data.mutex_msg)
			, ft_putstrfd(ERR_INIT_MUTEX, 2), EXIT_FAILURE);
	if (pthread_mutex_init(&general->data.mutex_lastmeal, NULL))
		return (pthread_mutex_destroy(&general->data.mutex_msg),
			pthread_mutex_destroy(&general->data.mutex_eat)
			, ft_putstrfd(ERR_INIT_MUTEX, 2), EXIT_FAILURE);
	if (pthread_mutex_init(&general->data.mutex_stop, NULL))
		return (pthread_mutex_destroy(&general->data.mutex_msg),
		pthread_mutex_destroy(&general->data.mutex_eat),
		pthread_mutex_destroy(&general->data.mutex_lastmeal),
		ft_putstrfd(ERR_INIT_MUTEX, 2), EXIT_FAILURE);
	if (pthread_mutex_init(&general->data.mutex_countmeal, NULL))
		return (pthread_mutex_destroy(&general->data.mutex_msg),
		pthread_mutex_destroy(&general->data.mutex_eat),
		pthread_mutex_destroy(&general->data.mutex_lastmeal),
		pthread_mutex_destroy(&general->data.mutex_stop),
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

int	initphilo(t_general *general, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < general->data.philo_nbr)
	{
		philo[i].id = (i + 1);
		philo[i].stop = 0;
		philo[i].data = &general->data;
		philo[i].general = general;
		philo[i].count_meal = 0;
		if (general->data.philo_nbr % 2 == 0)
		{
			philo[i].leftfork = general->data.mutex_fork[i];
			philo[i].rightfork = general->data.mutex_fork[(i + 1)
				% general->data.philo_nbr];
		}
		else
		{
			philo[i].leftfork = general->data.mutex_fork[(i + 1)
				% general->data.philo_nbr];
			philo[i].rightfork = general->data.mutex_fork[i];
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init(t_general *general, int argc, char **argv)
{
	if (initdata_checkargs(general, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	general->philo = (t_philo *)malloc(sizeof(t_philo)
			* general->data.philo_nbr);
	if (!general->philo)
		return (EXIT_FAILURE);
	memset(general->philo, 0, sizeof(t_philo) * general->data.philo_nbr);
	if (initdata_mutex(general) == EXIT_FAILURE)
		return (free(general->philo), EXIT_FAILURE);
	if (initforks_mutex(&general->data) == EXIT_FAILURE)
		return (free(general->philo), EXIT_FAILURE);
	if (initphilo(general, general->philo) == EXIT_FAILURE)
		return (ft_exit(general, general->philo, 5, general->data.philo_nbr),
			EXIT_FAILURE);
	general->data.start_time = get_time_ms();
	return (0);
}

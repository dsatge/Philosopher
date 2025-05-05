/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:21:16 by dsatge            #+#    #+#             */
/*   Updated: 2025/05/05 15:22:11 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_dell_mutexdata(t_data *data, int i)
{
	if (i >= 1)
		pthread_mutex_destroy(&data->mutex_msg);
	if (i >= 2)
		pthread_mutex_destroy(&data->mutex_lastmeal);
	if (i >= 3)
		pthread_mutex_destroy(&data->mutex_stop);
	if (i >= 4)
		pthread_mutex_destroy(&data->mutex_countmeal);
	return (0);
}

int	ft_dell_forks(t_data *data, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		pthread_mutex_destroy(data->mutex_fork[i]);
		i++;
	}
	return (0);
}

int	ft_exit(t_data *data, t_philo *philo, int dest_data, int dest_philo)
{
	if (dest_data > 0)
		ft_dell_mutexdata(data, dest_data);
	if (dest_philo > 0)
		ft_dell_forks(philo->data, dest_philo);
	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
	if (data->mutex_fork)
	{
		free(data->mutex_fork);
		data->mutex_fork = NULL;
	}
	return (EXIT_SUCCESS);
}

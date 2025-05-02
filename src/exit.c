/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:21:16 by dsatge            #+#    #+#             */
/*   Updated: 2025/05/02 17:56:19 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_exit(t_general *general, t_philo *philo, int dest_data, int dest_philo)
{
	if (dest_data > 0)
		ft_dell_mutexdata(general, dest_data);
	if (dest_philo > 0)
		ft_dell_forks(philo->data, dest_philo);
	if (general->philo)
	{
		free(general->philo);
		general->philo = NULL;
	}
	if (general->data.mutex_fork)
	{
		free(general->data.mutex_fork);
		general->data.mutex_fork = NULL;
	}
	return (EXIT_SUCCESS);
}

int	ft_dell_mutexdata(t_general *general, int i)
{
	if (i >= 1)
		pthread_mutex_destroy(&general->data.mutex_msg);
	if (i >= 2)
		pthread_mutex_destroy(&general->data.mutex_eat);
	if (i >= 3)
		pthread_mutex_destroy(&general->data.mutex_lastmeal);
	if (i >= 4)
		pthread_mutex_destroy(&general->data.mutex_stop);
	if (i >= 5)
		pthread_mutex_destroy(&general->data.mutex_countmeal);
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

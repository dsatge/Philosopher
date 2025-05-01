/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:21:16 by dsatge            #+#    #+#             */
/*   Updated: 2025/05/01 18:20:26 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_exit(t_general *general, t_philo *philo, int dest_data, int dest_philo)
{
	pthread_mutex_lock(&general->data.mutex_stop);
	if (general->data.stop == 0)
		general->data.stop = 1;
	pthread_mutex_unlock(&general->data.mutex_stop);
	if (dest_data > 0)
		ft_dell_mutexdata(general, dest_data);
	if (dest_philo > 0)
		ft_dell_forks(philo, dest_philo);
	if (general->philo)
	{
		free(general->philo);
		general->philo = NULL;
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
		pthread_mutex_destroy(&data->mutex_fork[i]);
		// pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (0);
}

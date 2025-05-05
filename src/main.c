/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:21:44 by dsatge            #+#    #+#             */
/*   Updated: 2025/05/05 15:04:30 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*stop_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_stop);
	philo->data->stop = 1;
	pthread_mutex_unlock(&philo->data->mutex_stop);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc < 5 || argc > 6)
	{
		ft_putstrfd("Error: Invalid number of arguments\n", 2);
		return (EXIT_FAILURE);
	}
	if (init(&data, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (philo_launch(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (ft_exit(&data, data.philo, 4, data.philo_nbr),
		EXIT_SUCCESS);
}

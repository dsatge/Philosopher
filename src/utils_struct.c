/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:01:34 by dsatge            #+#    #+#             */
/*   Updated: 2025/05/05 15:12:48 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	assign_forks(t_data *data, int i)
{
	if (data->philo[i].id % 2 == 0)
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
}

int	initdata_checkargs(t_data *data, int argc, char **argv)
{
	data->philo_nbr = convert_nbr(argv[1]);
	data->time_to_die = convert_nbr(argv[2]);
	data->time_to_eat = convert_nbr(argv[3]);
	data->time_to_sleep = convert_nbr(argv[4]);
	if (argc == 6)
		data->meals_limit = convert_nbr(argv[5]);
	else
		data->meals_limit = 0;
	if (check_parsing(data, argc) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_data(data, argc) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	data->meals_count = 0;
	data->stop = 0;
	data->start_time = -1;
	return (EXIT_SUCCESS);
}

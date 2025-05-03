/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:21:44 by dsatge            #+#    #+#             */
/*   Updated: 2025/05/03 14:06:20 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
	return (ft_exit(&data, data.philo, 3, data.philo_nbr),
		EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:21:44 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/30 13:55:47 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_general	general;

	memset(&general, 0, sizeof(general));
	if (argc < 5 || argc > 6)
	{
		ft_putstrfd("Error: Invalid number of arguments\n", 2);
		return (EXIT_FAILURE);
	}
	if (init(&general, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (philo_launch(&general) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (1)
	{
		ft_usleep(general.data.time_to_eat / 10, &general);
		if (wait_for_all(&general) == 0)
			break ;
	}
	return (ft_exit(&general, general.philo, 3, general.data.philo_nbr),
		EXIT_SUCCESS);
}

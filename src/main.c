/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:21:44 by dsatge            #+#    #+#             */
/*   Updated: 2025/05/02 16:45:07 by dsatge           ###   ########.fr       */
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
	return (ft_exit(&general, general.philo, 3, general.data.philo_nbr),
		EXIT_SUCCESS);
}

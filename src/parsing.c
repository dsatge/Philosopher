/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:22:10 by dsatge            #+#    #+#             */
/*   Updated: 2025/05/03 14:41:44 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	is_whitiespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r'
		|| c == '\n' || c == '\v' || c == '\f')
		return (0);
	return (1);
}

static int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (is_whitiespace(str[i]) == 0)
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		return (ft_putstrfd(ERR_NEG_DIGIT, 2), 1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (ft_putstrfd(ERR_PARS_NODIGIT, 2), 1);
		i++;
	}
	return (0);
}

int	convert_nbr(char *str)
{
	long int	nbr;
	int			i;

	i = 0;
	nbr = 0;
	if (is_digit(str) == 1)
		return (-1);
	while (str[i])
	{
		nbr = (nbr * 10) + (str[i] - 48);
		if (nbr > INT_MAX)
			return (ft_putstrfd(ERR_PARS_OUTRANGE, 2), -1);
		i++;
	}
	return ((int)nbr);
}

int	check_parsing(t_data *data, int ac)
{
	if (data->philo_nbr == -1
		|| data->time_to_die == -1
		|| data->time_to_eat == -1
		|| data->time_to_sleep == -1)
		return (EXIT_FAILURE);
	if (ac == 6 && data->meals_count == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_data(t_data *data, int ac)
{
	if (ac == 6 && (data->philo_nbr == 0
			|| data->time_to_die == 0
			|| data->time_to_eat == 0
			|| data->time_to_sleep == 0
			|| data->meals_count == 0))
		return (ft_putstrfd(ERR_PARS_ZERO, 2), EXIT_FAILURE);
	if (ac == 5 && (data->philo_nbr == 0
			|| data->time_to_die == 0
			|| data->time_to_eat == 0
			|| data->time_to_sleep == 0))
		return (ft_putstrfd(ERR_PARS_ZERO, 2), EXIT_FAILURE);
	if (data->philo_nbr > 200)
		return (ft_putstrfd(ERR_PARS_UP200, 2), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

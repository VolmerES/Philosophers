/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:15:44 by jdelorme          #+#    #+#             */
/*   Updated: 2025/01/16 14:37:18 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_negative_or_pos(char c)
{
	return ((c) == ' ' || c == '\t' || c == '+');
}

static size_t	ft_atosize_t(char *param)
{
	size_t	nbr;
	int		i;

	nbr = 0;
	i = 0;
	while (param[i])
	{
		while (ft_is_negative_or_pos(param[i]))
			i++;
		if (param[i] == '-')
			ft_error_exit(RED "Error: Wrong parameters\n"
				BLUE "Please note, negatives numbers are not allowed" RESET);
		else if (param[i] < '0' || param[i] > '9')
			ft_error_exit(RED "Error: Wrong parameters\n"
				BLUE "Please note, only numbers allowed" RESET);
		nbr = nbr * 10 + (param[i] - '0');
		i++;
		if (nbr > SIZE_MAX / 10 || (nbr == SIZE_MAX / 10
				&& (param[i] - '0') > SIZE_MAX % 10))
			ft_error_exit(RED "Error: Wrong parameters\n"
				BLUE "Please note, numbers are too big" RESET);
	}
	return (nbr);
}

void	ft_parsing_philo(t_table *table, char **params)
{
	table->philo_nbr = ft_atosize_t(params[1]);
	table->time_to_die = ft_atosize_t(params[2]) * 1000;
	table->time_to_eat = ft_atosize_t(params[3]) * 1000;
	table->time_to_sleep = ft_atosize_t(params[4]) * 1000;
	if (params[5])
	{
		table->nbr_limit_meals = ft_atosize_t(params[5]);
	}
	else
		table->nbr_limit_meals = -1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:34:08 by jdelorme          #+#    #+#             */
/*   Updated: 2025/01/14 12:54:43 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		ft_parsing_philo(&table, argv);
		ft_init_data(&table);
		ft_dinner_start(&table);
		ft_clean(&table);
	}
	else
		ft_error_exit(RED "Error: Wrong parameters\n"
			BLUE "Please use following format:\n"
			GREEN "./philo 5 800 200 300 [5]" RESET);
}

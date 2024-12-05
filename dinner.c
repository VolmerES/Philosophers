/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volmer <volmer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:42:27 by jdelorme          #+#    #+#             */
/*   Updated: 2024/12/04 22:08:28 by volmer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_start_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo*)data;
	ft_wait_for_threads(philo->table); // haciendose;
	return (NULL);
}

void	ft_dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->must_eat == 0)
		return ;
//	else if (table->philo_nbr = 1)
	else
	{
		while(table->philo_nbr > ++i)
			ft_thread_safe(&table->philos[i].philo_id, ft_start_simulation, &table->philos[i], CREATE);
	}
	ft_set_intbool(&table->must_eat, &table->bool_start_simulation, 1);
}
	

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volmer <volmer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:42:27 by jdelorme          #+#    #+#             */
/*   Updated: 2024/12/05 20:05:12 by volmer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_start_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo*)data;
	ft_wait_all_threads(philo->table); // haciendose;
	while (!ft_simulation_finish(philo->table))
	{
		//esta el filosofo lleno?
		if (philo->full)
			break;
		//comer
		ft_eat(philo);
		//sleep
		
		//think
		ft_thinking(philo);
	}
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
	table->bool_start_simulation = ft_gettime(MILLISECOND);
	ft_set_intbool(&table->must_eat, &table->bool_start_simulation, 1);
	i = -1;
	while (++i < table->philo_nbr)
		ft_thread_safe(&table->philos[i].philo_id, NULL, NULL, JOIN);
}
	

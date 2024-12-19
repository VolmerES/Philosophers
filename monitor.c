/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volmer <volmer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:38:01 by volmer            #+#    #+#             */
/*   Updated: 2024/12/19 18:43:47 by volmer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;
	
	if (ft_get_bool(&philo->philo_mutex_race, &philo->full))
		return (false);
	elapsed = ft_getime(MILLISECOND) - ft_get_long(&philo->philo_mutex_race, &philo->last_meal_time);
	time_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*ft_monitor_dinner(void *data)
{
	int i;
	t_table	*table;
	
	table = (t_table *)data;
	//Asegurar todos los filos estan activos
	while (!ft_all_threads_running(&table->table_mutex, &table->threads_running, table->philo_nbr))
		;
	while (!ft_simulation_finish(table))
	{
		
		i = -1;
		while (++i < table->philo_nbr && !ft_simulation_finish(table)) 
		{
			if (ft_philo_died(&table->philos[i]))
			{
				ft_write_status(DIED, &table->philos[i], DEBUG_MODE);
				ft_set_bool(&table->table_mutex, &table->end_simulation, true);
			}
		}
	}
	return (NULL);
}

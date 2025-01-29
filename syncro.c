/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volmer <volmer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:48:17 by volmer            #+#    #+#             */
/*   Updated: 2025/01/29 18:32:30 by volmer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_wait_all_threads(t_table *table)
{
	while (!ft_get_bool(&table->table_mutex, &table->threads_ready))
		;
}
void	ft_desync(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if(philo->id % 2 == 0)
			ft_precise_usleep(100, philo->table);
	}
	else
	{
		if (philo->id % 2 == 0)
			ft_thinking(philo, true);
	}
}

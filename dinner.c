/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volmer <volmer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:42:27 by jdelorme          #+#    #+#             */
/*   Updated: 2024/12/05 21:04:32 by volmer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_thinking(t_philo *philo)
{
	ft_write_status(THINKING, philo, DEBUG_MODE);
}

static void ft_eat(t_philo *philo)
{
	ft_mutex_safe(&philo->left_fork->fork, LOCK);
	ft_write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	ft_mutex_safe(&philo->right_fork->fork, LOCK);
	ft_write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);

	ft_set_long(&philo->philo_mutex_race, &philo->last_meal, ft_getime(MILLISECOND));
	philo->meal_count++;
	ft_write_status(EATING, philo, DEBUG_MODE);
	ft_precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->must_eat > 0 && philo->meal_count == philo->table->must_eat)
		ft_set_intbool(&philo->philo_mutex_race, &philo->full, 0);

	ft_mutex_safe(&philo->left_fork->fork, UNLOCK);
	ft_mutex_safe(&philo->right_fork->fork, UNLOCK);
}

void	*ft_start_simulation(void *data)
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
		ft_write_status(SLEEPING, philo, DEBUG_MODE);
		ft_precise_usleep(philo->table->time_to_sleep, philo->table);
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
			ft_thread_safe(&table->philos[i].philo, CREATE, ft_start_simulation, &table->philos[i]);
	}
	table->bool_start_simulation = ft_getime(MILLISECOND);
	ft_set_intbool(&table->table_mutex, &table->bool_start_simulation, 1);
	i = -1;
	while (++i < table->philo_nbr)
		ft_thread_safe(&table->philos[i].philo, JOIN, NULL, NULL);
}
	

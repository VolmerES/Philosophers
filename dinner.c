/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:42:27 by jdelorme          #+#    #+#             */
/*   Updated: 2025/01/14 12:43:16 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_alone_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	ft_wait_all_threads(philo->table);
	ft_set_long(&philo->philo_mutex_race,
		&philo->last_meal_time, ft_getime(MILLISECOND));
	ft_increase_long(&philo->table->table_mutex,
		&philo->table->threads_running);
	ft_write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!ft_simulation_finish((philo->table)))
		usleep(200);
	return (NULL);
}

static void	ft_thinking(t_philo *philo)
{
	ft_write_status(THINKING, philo, DEBUG_MODE);
	ft_precise_usleep(philo->table->time_to_sleep, philo->table);
}

static void	ft_eat(t_philo *philo)
{
	ft_mutex_safe(&philo->first_fork->fork, LOCK);
	ft_write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	ft_mutex_safe(&philo->second_fork->fork, LOCK);
	ft_write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	ft_set_long(&philo->philo_mutex_race,
		&philo->last_meal_time, ft_getime(MILLISECOND));
	philo->meal_count++;
	ft_write_status(EATING, philo, DEBUG_MODE);
	ft_precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meal_count == philo->table->nbr_limit_meals)
		ft_set_bool(&philo->philo_mutex_race, &philo->full, true);
	ft_mutex_safe(&philo->first_fork->fork, UNLOCK);
	ft_mutex_safe(&philo->second_fork->fork, UNLOCK);
}

void	*ft_start_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	ft_wait_all_threads(philo->table);
	ft_set_long(&philo->philo_mutex_race,
		&philo->last_meal_time, ft_getime(MILLISECOND));
	ft_increase_long(&philo->table->table_mutex,
		&philo->table->threads_running);
	while (!ft_simulation_finish(philo->table))
	{
		if (philo->full)
			break ;
		ft_eat(philo);
		ft_write_status(SLEEPING, philo, DEBUG_MODE);
		ft_precise_usleep(philo->table->time_to_sleep, philo->table);
		ft_thinking(philo);
	}
	return (NULL);
}

void	ft_dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		ft_thread_safe(&table->philos[0].philo_id,
			CREATE, ft_alone_philo, &table->philos[0]);
	else
	{
		while (table->philo_nbr > ++i)
		{
			ft_thread_safe(&table->philos[i].philo_id,
				CREATE, ft_start_simulation, &table->philos[i]);
		}
	}
	ft_thread_safe(&table->monitor, CREATE, ft_monitor_dinner, table);
	table->start_simulation = ft_getime(MILLISECOND);
	ft_set_bool(&table->table_mutex, &table->threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		ft_thread_safe(&table->philos[i].philo_id, JOIN, NULL, NULL);
	ft_set_bool(&table->table_mutex, &table->end_simulation, true);
	ft_thread_safe(&table->monitor, JOIN, NULL, NULL);
}

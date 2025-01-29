/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volmer <volmer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:23:15 by jdelorme          #+#    #+#             */
/*   Updated: 2025/01/29 19:34:34 by volmer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_assign_forks(t_philo *philo, t_fork *forks, int pos)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &forks[(pos + 1) % philo_nbr];
	philo->second_fork = &forks[pos];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[pos];
		philo->second_fork = &forks[(pos + 1) % philo_nbr];
	}
}

static void	ft_philosphers_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meal_count = 0;
		philo->table = table;
		ft_mutex_safe(&philo->philo_mutex_race, INIT);
		ft_assign_forks(philo, table->forks, i);
	}
}

void	ft_init_data(t_table *table)
{
	int	i;

	i = -1;
	table->threads_running = 0;
	table->end_simulation = false;
	table->threads_ready = false;
	table->philos = ft_malloc_safe(sizeof(t_philo) * table->philo_nbr);
	table->forks = ft_malloc_safe(sizeof(t_fork) * table->philo_nbr);
	ft_mutex_safe(&table->table_mutex, INIT);
	ft_mutex_safe(&table->write_locks, INIT);
	table->forks = ft_malloc_safe(sizeof(t_fork) * table->philo_nbr);
	while (++i < table->philo_nbr)
	{
		ft_mutex_safe(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	ft_philosphers_init(table);
}

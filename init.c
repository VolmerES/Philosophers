/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:23:15 by jdelorme          #+#    #+#             */
/*   Updated: 2024/10/24 18:59:19 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_assign_forks(t_philo *philo, t_fork *forks, int pos)
{

}

static void	ft_philosphers_init(t_table *table)
{
	int	i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		//? Esto hace que en compracion con los forks, los
		//? filos, tengan un numero mal al empezar por 1, CAMBIAR??
		philo->philo_id = i + 1;
		philo->full = -1;
		philo->meal_count = 0;
		philo->table = table;
		ft_assign_forks(philo, table->forks, i);
	}
}

void	ft_init_data(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = 0;
	table->philos = ft_malloc_safe(sizeof(t_philo) * table->philo_nbr);
	table->forks = ft_malloc_safe(sizeof(t_fork) * table->philo_nbr);
	while(++i < table->philo_nbr)
	{
		ft_mutex_safe(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	ft_philosophers_init(table);
}
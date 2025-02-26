/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:26:05 by volmer            #+#    #+#             */
/*   Updated: 2025/01/14 13:09:25 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_write_status_debug(t_philo_status status, t_philo *philo,
	long elapsed)
{
	if (TAKE_FIRST_FORK == status && !ft_simulation_finish(philo->table))
		printf("%6ld --> %d has taken de 1º fork %d \n", elapsed,
			philo->id, philo->first_fork->fork_id);
	else if (TAKE_SECOND_FORK == status && !ft_simulation_finish(philo->table))
		printf("%6ld --> %d has taken de 2º fork %d \n", elapsed, philo->id,
			philo->second_fork->fork_id);
	else if (EATING == status && !ft_simulation_finish(philo->table))
		printf("%6ld --> %d is eating --> %ld meals \n", elapsed, philo->id,
			philo->meal_count);
	else if (SLEEPING == status && !ft_simulation_finish(philo->table))
		printf("%6ld --> %d is thinking \n", elapsed, philo->id);
	else if (DIED == status && !ft_simulation_finish(philo->table))
		printf ("%6ld --> %d died \n", elapsed, philo->id);
}

void	ft_write_status(t_philo_status status, t_philo *philo, long debug)
{
	long	elapsed;

	elapsed = ft_getime(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return ;
	ft_mutex_safe(&philo->table->write_locks, LOCK);
	if (debug)
		ft_write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !ft_simulation_finish(philo->table))
			printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
		else if (EATING == status && !ft_simulation_finish(philo->table))
			printf("%-6ld %d is eating\n", elapsed, philo->id);
		else if (SLEEPING == status && !ft_simulation_finish(philo->table))
			printf("%-6ld %d is sleeping\n", elapsed, philo->id);
		else if (THINKING == status && !ft_simulation_finish(philo->table))
			printf("%-6ld %d is thinking\n", elapsed, philo->id);
		else if (DIED == status && !ft_simulation_finish(philo->table))
			printf("%-6ld %d died\n", elapsed, philo->id);
	}
	ft_mutex_safe(&philo->table->write_locks, UNLOCK);
}

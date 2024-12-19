/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volmer <volmer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:04:06 by volmer            #+#    #+#             */
/*   Updated: 2024/12/19 18:41:15 by volmer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_getime(t_time_code time_code)
{
	struct timeval	time_value;

	if (gettimeofday(&time_value, NULL))
		ft_error_exit("Get time of day failed");
	if (SECOND == time_code)
		return (time_value.tv_sec + (time_value.tv_usec / 1e6));
	else if (MILLISECOND == time_code)
		return ((time_value.tv_sec * 1e3) + (time_value.tv_usec / 1e3));
	else if (MICROSECOND == time_code)
		return ((time_value.tv_sec * 1e6) + (time_value.tv_usec));
	else
		ft_error_exit("Wrong input for getttime");
	return (1337);
}
void	ft_precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = ft_getime(MICROSECOND);
	while (ft_getime(MICROSECOND) - start < usec)
	{
		if (ft_simulation_finish(table))
			break ;
		elapsed = ft_getime(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (ft_getime(MICROSECOND) - start < usec)
				;
		}
	}
}

bool	ft_all_threads_running(t_mtx *mutex, long *threads_running, long philo_nbr)
{
	bool	ret;

	ret = false;
	ft_mutex_safe(mutex, LOCK);
	if (*threads_running == philo_nbr)
		ret = true;
	ft_mutex_safe(mutex, UNLOCK);
	return (ret);
}

void	ft_increase_long(t_mtx *mutex, long *dest)
{
	ft_mutex_safe(mutex, LOCK);
	*dest += 1;
	ft_mutex_safe(mutex, UNLOCK);
}
void	ft_clean(t_table *table)
{
	t_philo	*philo;
	int	i;

	i = -1;
	while(++i < table->philo_nbr)
	{
		philo = table->philos + i;
		ft_mutex_safe(&philo->philo_mutex_race, DESTROY);
	}
	ft_mutex_safe(&table->table_mutex, DESTROY);
	ft_mutex_safe(&table->write_locks, DESTROY);
	free(table->philos);
	free(table->forks);
}
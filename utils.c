/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volmer <volmer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:04:06 by volmer            #+#    #+#             */
/*   Updated: 2024/12/05 21:07:06 by volmer           ###   ########.fr       */
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
			usleep(usec / 2);
		else
		{
			while (ft_getime(MICROSECOND) - start < usec)
				;
		}
	}
}

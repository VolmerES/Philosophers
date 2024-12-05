/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setgetter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volmer <volmer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:34:50 by volmer            #+#    #+#             */
/*   Updated: 2024/12/04 22:04:02 by volmer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_set_intbool(t_mtx *mutex, int *dest, int value)
{
	ft_mutex_safe(mutex, LOCK);
	*dest = value;
	ft_mutex_safe(mutex, UNLOCK);
}

int		ft_get_intbool(t_mtx *mutex, int *value)
{
	int	res;

	ft_mutex_safe(mutex, LOCK);
	res = *value;
	ft_mutex_safe(mutex, UNLOCK);
	return (res);
}

long	ft_get_long(t_mtx *mutex, long *value)
{
	long	res;

	ft_mutex_safe(mutex, LOCK);
	res = *value;
	ft_mutex_safe(mutex, UNLOCK);
	return (res);
}

void	ft_set_long(t_mtx *mutex, long *dest, long value)
{
	ft_mutex_safe(mutex, LOCK);
	*dest = value;
	ft_mutex_safe(mutex, UNLOCK);
}

int		ft_simulation_finish(t_table *table)
{
	return (ft_get_intbool(&table->table_mutex, &table->end_simulation));
}
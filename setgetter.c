/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setgetter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:34:50 by volmer            #+#    #+#             */
/*   Updated: 2025/01/14 12:56:30 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_set_bool(t_mtx *mutex, bool *dest, bool value)
{
	ft_mutex_safe(mutex, LOCK);
	*dest = value;
	ft_mutex_safe(mutex, UNLOCK);
}

bool	ft_get_bool(t_mtx *mutex, bool *value)
{
	bool	res;

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

bool	ft_simulation_finish(t_table *table)
{
	return (ft_get_bool(&table->table_mutex, &table->end_simulation));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volmer <volmer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:48:17 by volmer            #+#    #+#             */
/*   Updated: 2024/12/05 18:59:43 by volmer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "philo.h"

void	ft_wait_all_threads(t_table *table)
{
	while (!ft_get_intbool(&table->table_mutex, &table->bool_threads_ready))
	{
		wait;
	}
}

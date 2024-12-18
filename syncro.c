/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volmer <volmer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:48:17 by volmer            #+#    #+#             */
/*   Updated: 2024/12/18 21:58:41 by volmer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "philo.h"

void	ft_wait_all_threads(t_table *table)
{
	while (!ft_get_bool(&table->table_mutex, &table->threads_ready))
		;
}

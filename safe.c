/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:53:28 by jdelorme          #+#    #+#             */
/*   Updated: 2024/10/24 17:54:16 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_mutex_safe(t_mtx *mutex, t_code code)
{
	if (code == INIT)
		ft_error_mutex(code, pthread_mutex_init(mutex, NULL));
	else if (code == UNLOCK)
		ft_error_mutex(code, pthread_mutex_unlock(mutex));
	else if (code == LOCK)
		ft_error_mutex(code, pthread_mutex_lock(mutex));
	else if (code == DESTROY)
		ft_error_mutex(code, pthread_mutex_destroy(mutex));
	else
		ft_error_exit(RED "Error: Mutex operation not found\n" RESET);
}

void	*ft_malloc_safe(size_t size)
{
	void	*ptr;
	
	ptr = malloc(size);
	if (!ptr)
		ft_error_exit(RED "Error: Malloc failed\n" RESET);
	printf("Malloc success\n");
	return (ptr);
}

void	ft_thread_safe(pthread_t *thread, t_code code, void *(*func)(void *), void *arg)
{
	if (code == CREATE)
		ft_error_thread(code, pthread_create(thread, NULL, func, arg));
	else if (code == JOIN)
		ft_error_thread(code, pthread_join(*thread, NULL));
	else if (code == DETACH)
		ft_error_thread(code, pthread_detach(*thread));
	else
		ft_error_exit(RED "Error: Thread operation not found\n" RESET);
}
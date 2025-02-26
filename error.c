/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:54:35 by jdelorme          #+#    #+#             */
/*   Updated: 2025/01/14 12:49:47 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error_exit(char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

void	ft_error_mutex(t_code code, int status)
{
	if (status == 0)
		return ;
	if (status == EINVAL)
		ft_error_exit(RED "Error: The value specified"
			" by mutex is invalid\n" RESET);
	else if (status == EBUSY)
		ft_error_exit(RED "Error: The implementation has detected an attempt"
			" to destroy the object referenced by mutex while it is locked or"
			" referenced by another thread\n" RESET);
	else if (status == EAGAIN)
		ft_error_exit(RED "Error: The system lacked the necessary resources"
			" to initialise another mutex\n" RESET);
	else if (status == EDEADLK)
		ft_error_exit(RED "Error: A deadlock condition was detected or the"
			" current thread already owns the mutex\n" RESET);
	else if (status == EPERM)
		ft_error_exit(RED "Error: The current thread does not"
			" own the mutex\n" RESET);
	else
		ft_error_exit(RED "Error: Mutex operation not found\n" RESET);
}

void	ft_error_thread(t_code code, int status)
{
	if (status == 0)
		return ;
	else if ((code == DETACH || code == JOIN) && status == EINVAL)
		ft_error_exit(RED "Error: Thread is not joinable or another"
			" thread is already waiting to join with this thread\n" RESET);
	else if ((code == DETACH || code == JOIN) && status == ESRCH)
		ft_error_exit(RED "Error: No thread with the ID thread"
			" could be found\n" RESET);
	else if (code == JOIN && status == EDEADLK)
		ft_error_exit(RED "Error: A deadlock was detected\n" RESET);
	else if (code == CREATE && status == EPERM)
		ft_error_exit(RED "Error: No permission to set the"
			" scheduling policy"
			" and parameters specified in attr.\n" RESET);
}

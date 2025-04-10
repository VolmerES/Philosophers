/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volmer <volmer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:24:45 by jdelorme          #+#    #+#             */
/*   Updated: 2025/01/29 18:34:33 by volmer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* pthread_create, pthread_join, pthread_mutex_init, 
pthread_mutex_lock, pthread_mutex_unlock*/
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
// gettimeofday
# include <sys/time.h>
# include <limits.h>
# include "libft/libft.h"
// Para las macros de salidas de error de mutex 
# include <errno.h>
# include <stdbool.h>
# include <stdint.h>

# define RED     "\x1B[31m"
# define GREEN   "\x1B[32m"
# define BLUE    "\x1B[34m"
# define RESET   "\x1B[0m"
# define DEBUG_MODE 0

//          PARAMETROS DE FILO           //
//---------------------------------------//
//?  ./philo   5    800   200   300  [5]
//?  5   ---> Numero de filosofos
//?  800 ---> Tiempo para morir
//?  200 ---> Tiempo para comer
//?  300 ---> Tiempo para dormir
//?  [5] ---> Veces que cada filo debe comer
//--------------------------------------//

//----------DEFINES LEGIBILIDAD---------//
//     Mutex definido mas corto
typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

//-------------ESTRUCTURAS--------------//
//! ESTRUCTURA ESTADO DEL PHILO
typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}			t_philo_status;

//! ESTRUCTURA PARA GETTIME
typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}			t_time_code;

//! ESTRUCTURA DE CODIGOS DE OPERACION MUTEX//
typedef enum e_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_code;

//! (ESTRUCTURA TENEDORES (FORKS) "MUTEX THREADS")//
typedef struct s_fork
{
	/*Mutex de los filos*/
	t_mtx		fork;
	/*Identificador del mutex*/
	int			fork_id;
}			t_fork;

//! (ESTRUCTURA DE FILOSOFOS (THREADS))//
typedef struct s_philo
{
	/*Identificador del filosofo*/
	int			id;
	/*Cantidad de comidas del filo*/
	long		meal_count;
	/*Flag booleana*/
	bool		full;
	/*Tiempo desde la ulima comida*/
	long		last_meal_time;

	/*Mutex izquierdo del filo*/
	t_fork		*first_fork;

	/*Mutex derecho del filo*/
	t_fork		*second_fork;

	/*Hilos, aka filosofos*/
	pthread_t	philo_id;

	t_mtx		philo_mutex_race;

	t_table		*table;
}			t_philo;

typedef struct s_table
{
	size_t		philo_nbr;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		nbr_limit_meals;
	long		start_simulation;
	long		threads_running;
	bool		end_simulation;
	bool		threads_ready;
	pthread_t	monitor;
	t_fork		*forks;
	t_philo		*philos;
	t_mtx		table_mutex;
	t_mtx		write_locks;
}				t_table;

/*     FUNCIONES     */
/**/
/*				ERROR.C				*/
int		ft_error_exit(char *error);
void	ft_error_mutex(t_code code, int status);
void	ft_error_thread(t_code code, int status);

/* 			    PARSING.C  			*/
void	ft_parsing_philo(t_table *table, char **params);

/* 			    INIT.C  			*/
void	ft_init_data(t_table *table);

/* 				SAFE.C				*/
void	ft_mutex_safe(t_mtx *mutex, t_code code);
void	*ft_malloc_safe(size_t size);
void	ft_thread_safe(pthread_t *thread, t_code code,
			void *(*func)(void *), void *arg);

/*				DINNER.C			*/
void	ft_dinner_start(t_table *table);
void	*ft_start_simulation(void *data);
void	ft_thinking(t_philo *philo, bool sync);

/*				SERGETEER.C			*/
bool	ft_simulation_finish(t_table *table);
void	ft_set_long(t_mtx *mutex, long *dest, long value);
long	ft_get_long(t_mtx *mutex, long *value);
bool	ft_get_bool(t_mtx *mutex, bool *value);
void	ft_set_bool(t_mtx *mutex, bool *dest, bool value);

/*				SYNCHRO				*/
void	ft_wait_all_threads(t_table *table);
void	ft_desync(t_philo *philo);

/*				UTILS				*/
long	ft_getime(t_time_code time_code);
void	ft_precise_usleep(long usec, t_table *table);
bool	ft_all_threads_running(t_mtx *mutex, long *threads_running,
			long philo_nbr);
void	ft_increase_long(t_mtx *mutex, long *dest);
void	ft_clean(t_table *table);

/*				WRITE				*/
void	ft_write_status(t_philo_status status, t_philo *philo, long debug);

/*				MONITOR				*/
void	*ft_monitor_dinner(void *data);

#endif
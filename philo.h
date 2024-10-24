/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:24:45 by jdelorme          #+#    #+#             */
/*   Updated: 2024/10/24 18:30:04 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h> // pthread_create, pthread_join, pthread_mutex_init, pthread_mutex_lock, pthread_mutex_unlock
#include <unistd.h> // usleep
#include <stdio.h> // printf
#include <stdlib.h> // malloc, free
#include <sys/time.h> // gettimeofday
#include <limits.h> // INT_MAX
#include "libft/libft.h" 
#include <errno.h> // Para las macros de salidas de error de mutex

#define RED     "\x1B[31m"  // Rojo
#define GREEN   "\x1B[32m"  // Verde
#define BLUE    "\x1B[34m"  // Azul
#define RESET   "\x1B[0m"   // Reset color in terminal



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
typedef		pthread_mutex_t	t_mtx;


//-------------ESTRUCTURAS--------------//

//! ESTRUCTURA 


//! ESTRUCTURA DE CODIGOS DE OPERACION MUTEX//
typedef enum	e_code
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
typedef struct	s_fork
{
	/*Mutex de los filos*/
	t_mtx		fork;
	/*Identificador del mutex*/
	int			fork_id;
}			t_fork;

//! (ESTRUCTURA DE FILOSOFOS (THREADS))//
typedef	struct	s_philo
{
	/*Identificador del filosofo*/
	int			philo_id;
	/*Cantidad de comidas del filo*/
	long		meal_count;
	/*Flag booleana*/
	int			full;
	/*Tiempo desde la ulima comida*/
	long		last_meal;
	
	/*Mutex izquierdo del filo*/
	t_fork		*left_fork;
	
	/*Mutex derecho del filo*/
	t_fork		*right_fork;

	/*Hilos, aka filosofos*/
	pthread_t	philo;
	
	t_table		*table;
}			t_philo;

typedef struct	s_table
{
	size_t	philo_nbr;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	must_eat;
	long	start_simulation;
	int		end_simulation;
	t_fork	*forks;
	t_philo	*philos;
}				t_table;


/*     FUNCIONES     */

/*				ERROR.C				*/
int	ft_error_exit(char *error);
void	ft_error_mutex(t_code code, int status);
void	ft_error_thread(t_code code, int status);


/* 			    PARSING.C  			*/
void	ft_parsing_philo(t_table *table, char **params);


/* 			    INIT.C  			*/
void	ft_init_data(t_table *table);

/* 				SAFE.C				*/
void	ft_mutex_safe(t_mtx *mutex, t_code code);
void	*ft_malloc_safe(size_t size);
void	ft_thread_safe(pthread_t *thread, t_code code, void *(*func)(void *), void *arg);
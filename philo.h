/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:24:45 by jdelorme          #+#    #+#             */
/*   Updated: 2024/10/16 16:02:21 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h> // pthread_create, pthread_join, pthread_mutex_init, pthread_mutex_lock, pthread_mutex_unlock
#include <unistd.h> // usleep
#include <stdio.h> // printf
#include <stdlib.h> // malloc, free
#include <sys/time.h> // gettimeofday
#include <limits.h> // INT_MAX

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
typdef struct	s_table
{
	
}				t_table;


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
}			t_philo;
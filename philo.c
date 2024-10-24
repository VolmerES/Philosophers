/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:34:08 by jdelorme          #+#    #+#             */
/*   Updated: 2024/10/24 16:48:30 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//          PARAMETROS DE FILO           //
//---------------------------------------//
//?  ./philo   5    800   200   300  [5]
//?  5   ---> Numero de filosofos
//?  800 ---> Tiempo para morir
//?  200 ---> Tiempo para comer
//?  300 ---> Tiempo para dormir
//?  [5] ---> Veces que cada filo debe comer (opcional);
//--------------------------------------//


/*           ESTRUCTURA DEL PROYECO          */
//?	 1.-Checkeo de errores (parsing input)       //  OK
//?  2.-Creacion de hilos (data inicialitation)
//  		a) End simulation tenemos que establecerlo en falso
//  		b) Tenemos que reservar malloc para los filosofos
//  		c) Respescto a b Tenemos que hacer una funcion para los mallocs (orden) y quedevuelva NUll en caso de fallo
//
//?  3.-Inicio de cena (dinner start)
//?  4.-Limpieza de hilos (leaks cleaner)
//-------------------------------------------//

int	main(int argc, char **argv)
{
	t_table	table;
	
	if (argc == 5 || argc == 6)
	{
		ft_parsing_philo(&table, argv);
		ft_init_data(&table);
	}
	else
		ft_error_exit(RED "Error: Wrong parameters\n"
		BLUE "Please use following format:\n"
		GREEN "./philo 5 800 200 300 [5]" RESET);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:34:08 by jdelorme          #+#    #+#             */
/*   Updated: 2024/10/23 18:54:35 by jdelorme         ###   ########.fr       */
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
//?	 1.-Checkeo de errores (parsing input)
//*			D) Comprobar que los timestamps sean mayores que 60 ms
//*			E) Comprobar si tenemos argumento 5. En caso contrario establecer en - 1, como flag

//?  2.-Creacion de hilos (data inicialitation)
//?  3.-Inicio de cena (dinner start)
//?  4.-Limpieza de hilos (leaks cleaner)
//-------------------------------------------//

int	main(int argc, char **argv)
{
	t_table	table;
	
	if (argc == 5 || argc == 6)
	{
		ft_parsing_philo(table, argv);
	}
	else
		ft_error_exit(RED "Error: Wrong parameters\n"
		BLUE "Please use following format:\n"
		GREEN "./philo 5 800 200 300 [5]" RESET);
}
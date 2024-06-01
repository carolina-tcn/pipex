/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:20:16 by carolinatac       #+#    #+#             */
/*   Updated: 2024/06/01 12:50:20 by ctacconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
	
//los argumentos son 4: archivo1 comando1 comando2 archivo 2 (comandos de shell con sus parametros)

int	main(int argc, char **argv, char **envp)
{
	envp: array de cadena de chars que contiene las variables del entorno del programa
	cada cadena es una variable de entorno en el formato VARIABLE=valor
	
	- gestion de argumentos

	- abrir el infile en modo lectura

	- abrir el outfile en modo escritura, se crea si no exist y trunca si si 

	- crear la pipe (con pipefd?) para comunicar comando1 y comando2


Redirecciones:
	- primer proceso hijo para comando1

	- segundo proceso hijo para comando2

	- cerrar y esperar

	return (0);
}

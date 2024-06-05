/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:20:16 by carolinatac       #+#    #+#             */
/*   Updated: 2024/06/05 20:02:45 by ctacconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
	
//los argumentos son 4: archivo1 comando1 comando2 archivo 2 (comandos de shell con sus parametros)

void	arg_error(void)
{
	ft_putstr_fd("Error\nEx: ./pipex infile cmd1 cmd2 outfile\n", STDERR_FILENO);
	exit (EXIT_FAILURE);
}

void	error(void)
{
	perror("ERROR\n");
	exit (EXIT_FAILURE);
}

//tengo el proceso hijo creado
void	child_process(int *fd, char **argv, char **envp)
{
	int	open(const char *path, int flags)
		- for reading, writing or both
	
}

void	parent_process(int *fd, char **argv, char **envp)
{
	
}
Redirecciones:
	- primer proceso hijo para comando1
	- segundo proceso hijo para comando2
	- cerrar y esperar
	
int	main(int argc, char **argv, char **envp)
{
	envp: array de cadena de chars que contiene las variables del entorno del programa
	cada cadena es una variable de entorno en el formato VARIABLE=valor
	int		fd[2];
	pid_t	pid_process;

	if (argc != 5)
		arg_error();
	//int pipe(int pipefd[2]); si ret 0 success, -1 error. creo la pipe para comunicar los cmnds
	if (pipe(fd) == -1)
		error();
	pid = fork(); //crea un nuevo proceso copiando el actual, creo padre e hijo y como llamo a  
					//pipe se comunican entre ellos
					//estan integrados	
	if (pid_process < 0)
		error();
	else if (!pid_process)
		child_process(fd, argv, envp);
	else
		parent_process(fd, argv, envp);

	- gestion de argumentos
	- abrir el infile en modo lectura
	- abrir el outfile en modo escritura, se crea si no exist y trunca si si 
	- crear la pipe (con pipefd?) para comunicar comando1 y comando2
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:20:16 by carolinatac       #+#    #+#             */
/*   Updated: 2024/06/06 23:10:26 by ctacconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;
	int		i;
	
	i = 0;
	cmd = ft_split(argv, ' ');
	path = ft_path(cmd[0], envp);
}

void	child_process(int *fd, char **argv, char **envp)
{
	/*int	open(const char *path(el ejecutable del programa), int flags)
		- for reading, writing or both
	int	dup2(int fd1, int fd2)
		- cierra fd y duplica el valor de fd2 a fd1, redirige f1 a f2
	-abrir archivo para lectura
	-duplico para que sea este fd -> dup2
	-duplico de nuevo*/
	int	infile;
	//open me devuelve un fd que asigno a infile
	//abro el infile en modo lectura
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		error();
	dup2(fd[WRITE_END], STDOUT_FILENO); //redirecciono stdout para escribir en el extremo de escritura del pipe
	dup2(infile, STDIN_FILENO); //redirecciono stdin para que lea archivo 1
	close(fd[READ_END]); //CIERRO EXTREMO NO NECESARIO
	execute(argv(2), envp);
}

void	parent_process(int *fd, char **argv, char **envp)
{
	int	outfile;
	//se crea si no existe y trunca si si
	outfile = open(argv(4), O_WRONLY | O_CREAT | O_TRUNC, 0666)
	if (outfile == -1)
		error();
	dup2(fd[READ_END], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[WRITE_END]);
	execute(argv(3), envp);
}

int	main(int argc, char **argv, char **envp)
{
	envp: array de cadena de chars que contiene las variables del entorno del programa
	cada cadena es una variable de entorno en el formato VARIABLE=valor
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		arg_error();
	//int pipe(int pipefd[2]); si ret 0 success, -1 error. creo la pipe para comunicar los cmnds
	//comunico los dos comandos
	//EL PROCESO PADRE ES CREADO POR EL PADRE
	if (pipe(fd) == -1)
		error();
	//pid_t fork(void)
	pid = fork(); //crea un nuevo proceso hijo copiando el actual, creo padre e hijo y como llamo a  
					//pipe se comunican entre ellos
					//estan integrados	
	if (pid_process < 0)
		error();
	else if (!pid_process)
		child_process(fd, argv, envp);
	else
		parent_process(fd, argv, envp);
	return (0);
}

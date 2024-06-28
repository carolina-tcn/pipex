/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:01:22 by ctacconi          #+#    #+#             */
/*   Updated: 2024/06/28 17:01:26 by ctacconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/*void	debug(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}*/
//int execve(const char *path, char *const argv[], char *envp[]);
void	execute(char *argv, char **envp)
{
	char	*path_cmd;
	char	**s_cmd;

	s_cmd = ft_split(argv, ' ');
	if (s_cmd == NULL)
		//error(2);
		handle_error(NULL, NULL, 2);
	path_cmd = get_path(s_cmd[0], envp);
	if (path_cmd == NULL)
	/*{
		ft_free(s_cmd);
		error(3);
	}*/
		handle_error(s_cmd, NULL, 3);
	if (execve(path_cmd, s_cmd, envp) == -1)
	/*{	
		ft_free(s_cmd);
		free(path_cmd);
		error(4);
	}*/
		handle_error(s_cmd, path_cmd, 4);

//On success, execve() does not return, on error -1 is returned,
//TENGO QUE LIBERAR AQUI???
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
	close(fd[READ_END]); //CIERRO EXTREMO NO NECESARIO
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		error(7);
	if (dup2(fd[WRITE_END], STDOUT_FILENO) == -1) //redirecciono stdout para escribir en el extremo de escritura del pipe
	{
		//debug("primer dup del hijo");
		close(infile);
		error(6);
	}
	if (dup2(infile, STDIN_FILENO) == -1) //redirecciono stdin para que lea archivo 1
	{
		//debug("segundo dup del hijo");
		close(infile);
		error(6);
	}
	execute(argv[2], envp);
	close(infile);
}

void	parent_process(int *fd, char **argv, char **envp)
{
	int	outfile;

	close(fd[WRITE_END]);
	//se crea si no existe y trunca si si
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (outfile == -1)
		error(1);
	if (dup2(fd[READ_END], STDIN_FILENO) == -1)
	{
		//debug("primer dup del padre");
		close(outfile);
		error(6);
	}
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		//debug("segundo dup del padre");
		close(outfile);
		error(6);
	}
	execute(argv[3], envp);
	close(outfile);
}

int	main(int argc, char **argv, char **envp)
{
	//env: array de cadena de chars que contiene las variables del entorno del programa
	//cada cadena es una variable de entorno en el formato VARIABLE=valor
	int		fd[2];
	int		status;
	pid_t	pid;

	if (argc != 5)
		error(5);
	//int pipe(int pipefd[2]); si ret 0 success, -1 error. creo la pipe para comunicar los cmnds
	//comunico los dos comandos
	//EL PROCESO PADRE ES CREADO POR EL PADRE
	if (pipe(fd) == -1)
		error(1);
	//pid_t fork(void)
	pid = fork(); //crea un nuevo proceso hijo copiando el actual, creo padre e hijo y como llamo a  
					//pipe se comunican entre ellos
					//estan integrados	
	if (pid < 0)
		error(1);
	//printf("fork successful\n");
	if (!pid)
	{
		//printf("Child: I'm the child, my internal pid is %d.\n", pid);
		child_process(fd, argv, envp);
	}
	wait(&status); //el status es para el wait del padre
	if (pid)
	{
		//printf("Parent: I'm the parent, my child's pid is %d.\n", pid);
		parent_process(fd, argv, envp);
	}
	return (EXIT_SUCCESS);
}
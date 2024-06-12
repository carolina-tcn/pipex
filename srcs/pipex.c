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

void	error(int num_error)
{
	if (num_error == 1)
		perror("ERROR\n");
	if (num_error == 2)
		perror("Error splitting command\n");
	if (num_error == 3)
	{
		perror("Command not found\n");
		exit(127);
	}
	if (num_error == 4)
		perror("Error executing command\n");
	if (num_error == 5)
		ft_putstr_fd("Usage: <./pipex infile cmd1 cmd2 outfile>\n", 2);
	if (num_error == 6)
		perror("Error with dup2");
	exit (EXIT_FAILURE);
}
void ft_free(char	**strs)
{
	int	i;

	i = 0;
	while()
}

char *get_path(char *cmd, char **envp)
{
	char	*path_cmd;
	char	*path;
	char	**envp_path;
	int		i;
            	i = 0;
	while(envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	envp_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while(envp_path[i])
	{
		path = ft_strjoin(envp_path[i], "/");
		if (!path)
		{
			ft_free(envp_path);
		}
		i++;
	}
	           
	return();
}

//int execve(const char *path, char *const argv[], char *envp[]);
void	execute(char *argv, char **envp)
{
	char	*path_cmd;
	char	**s_cmd;
	int		i;

	s_cmd = ft_split(argv, ' ');
	if (s_cmd == NULL)
		error(2);
	path_cmd = get_path(s_cmd[0], envp);
	if (path_cmd == NULL)
	{
		while (s_cmd[i])
		{
			free(s_cmd[i]);
			i++;
		}
		free(s_cmd);
		error(3);
	}
	if (execve(path_cmd, s_cmd, envp) == -1)
		error(4);
		//frees

//On success, execve() does not return, on error -1 is returned,
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
		error(1);
	if (dup2(fd[WRITE_END], STDOUT_FILENO) == -1) //redirecciono stdout para escribir en el extremo de escritura del pipe
	{
		close(infile);
		error(6);
	}
	dup2(infile, STDIN_FILENO); //redirecciono stdin para que lea archivo 1
	{
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
	outfile = open(argv[4]), O_WRONLY | O_CREAT | O_TRUNC, 0666)
	if (outfile == -1)
		error(1);
	if (dup2(fd[READ_END], STDIN_FILENO) == -1)
	{
		close(outfile);
		error(6);
	}
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		close(outfile);
		error(6);
	}
	execute(argv[3], envp);
	close(outfile);
}

int	main(int argc, char **argv, char **envp)
{
	env: array de cadena de chars que contiene las variables del entorno del programa
	cada cadena es una variable de entorno en el formato VARIABLE=valor
	int		fd[2];
	int		status;
	pid_t	pid;

	if (argc != 5)
		arg_error(5);
	//int pipe(int pipefd[2]); si ret 0 success, -1 error. creo la pipe para comunicar los cmnds
	//comunico los dos comandos
	//EL PROCESO PADRE ES CREADO POR EL PADRE
	if (pipe(fd) == -1)
		error(1);
	//pid_t fork(void)
	pid = fork(); //crea un nuevo proceso hijo copiando el actual, creo padre e hijo y como llamo a  
					//pipe se comunican entre ellos
					//estan integrados	
	if (pid_process < 0)
		error(1);
	if (!pid_process)
		child_process(fd, argv, envp);
	wait(&status); //el status es para el wait del padre
	id (pid_process)
		parent_process(fd, argv, envp);
	return (0);
}

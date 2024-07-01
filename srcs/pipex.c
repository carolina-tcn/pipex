/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:01:22 by ctacconi          #+#    #+#             */
/*   Updated: 2024/07/01 22:07:10 by ctacconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	execute(char *argv, char **envp)
{
	char	*path_cmd;
	char	**s_cmd;

	s_cmd = ft_split(argv, ' ');
	if (s_cmd == NULL)
		handle_error(NULL, NULL, 2);
	path_cmd = get_path(s_cmd[0], envp, 0, NULL);
	if (path_cmd == NULL)
		handle_error(s_cmd, NULL, 3);
	if (execve(path_cmd, s_cmd, envp) == -1)
		handle_error(s_cmd, path_cmd, 4);
}

void	child_process(int *fd, char **argv, char **envp)
{
	int	infile;

	close(fd[READ_END]);
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		error(7);
	if (dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
	{
		close(infile);
		error(6);
	}
	if (dup2(infile, STDIN_FILENO) == -1)
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
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
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
	pid_t	pid;
	int		fd[2];
	int		status;

	if (argc != 5)
		error(5);
	if (pipe(fd) == -1)
		error(1);
	pid = fork();
	if (pid < 0)
		error(1);
	if (!pid)
		child_process(fd, argv, envp);
	wait(&status);
	if (pid)
		parent_process(fd, argv, envp);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:20:17 by ctacconi          #+#    #+#             */
/*   Updated: 2024/06/28 16:20:21 by ctacconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	handle_error(char **s_cmd, char *path_cmd, int error_code)
{
	if (s_cmd)
        ft_free(s_cmd);
    if (path_cmd)
        free(path_cmd);
    error(error_code);
}

void	error(int num_error)
{
	if (num_error == 1)
		perror("ERROR");
	else if (num_error == 2)
		perror("error splitting command\n");
	else if (num_error == 3)
	{
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
	else if (num_error == 4)
		perror("error executing command\n");
	else if (num_error == 5)
		ft_putstr_fd("ERROR-Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
	else if (num_error == 6)
		perror("error with dup2");
	else if (num_error == 7)
		perror("infile");
	exit (EXIT_FAILURE);
}

void ft_free(char **strs)
{
	int	i;

	i = 0;
	while(strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

//manejo tanto comandos simples como rutas absolutas
//F_OK check the existance of the file
char *get_path(char *cmd, char **envp)
{
	char	*path_cmd;

	if (access(cmd, F_OK | X_OK) == 0)
	{
		path_cmd = ft_strdup(cmd);
		if (!path_cmd)
			error (1);
		return (path_cmd);
	}
	char	*path;
	char	**envp_path;
	int		i;
    
	i = 0;
	while(envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (!envp[i])
		return (NULL);
	envp_path = ft_split(envp[i] + 5, ':');
	if (!envp_path)
		error(3);
	i = 0;
	while(envp_path[i])
	{
		path = ft_strjoin(envp_path[i], "/");
		if (!path)
		{	
			ft_free(envp_path);
			error(1);
		}
		path_cmd = ft_strjoin(path, cmd);
		free(path);
		if (!path_cmd)
		{
			ft_free(envp_path);
			error(1);
		}
		if (access(path_cmd, F_OK | X_OK) == 0)
		{
			ft_free(envp_path);
			return (path_cmd);
		}
		free(path_cmd);
		i++;
	}
	ft_free(envp_path);
	return(NULL);
}
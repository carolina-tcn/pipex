/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinatacconis <carolinatacconis@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:31:23 by carolinatac       #+#    #+#             */
/*   Updated: 2024/06/13 11:52:03 by carolinatac      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	error(int num_error)
{
	if (num_error == 1)
		perror("ERROR");
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
	if (num_error == 7)
		perror("Infile");
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
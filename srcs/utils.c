/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:20:17 by ctacconi          #+#    #+#             */
/*   Updated: 2024/07/03 15:41:35 by ctacconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	handle_error(char *argv, char **s_cmd, char *path_cmd, int error_code)
{
	if (s_cmd)
		ft_free(s_cmd);
	if (path_cmd)
		free(path_cmd);
	error(error_code, argv);
}

void	error(int num_error, char *str)
{
	if (num_error == 1)
		perror("ERROR");
	else if (num_error == 2)
		perror("error splitting command\n");
	else if (num_error == 3)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	else if (num_error == 4)
		perror("error executing command\n");
	else if (num_error == 5)
		ft_putstr_fd("ERROR-Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
	else if (num_error == 6)
		perror("error with dup2");
	else if (num_error == 7)
		perror(str);
	exit (EXIT_FAILURE);
}

void	ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	*get_path(char *cmd, char **envp, int i, char *path_cmd)
{
	char	**envp_path;

	if (access(cmd, F_OK | X_OK) == 0)
	{
		path_cmd = ft_strdup(cmd);
		if (!path_cmd)
			error (1, NULL);
		return (path_cmd);
	}
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (!envp[i])
		return (NULL);
	envp_path = ft_split(envp[i] + 5, ':');
	if (!envp_path)
		error(3, NULL);
	i = -1;
	path_cmd = ft_aux(0, envp_path, cmd, path_cmd);
	if (path_cmd)
		return (path_cmd);
	ft_free(envp_path);
	return (NULL);
}

char	*ft_aux(int i, char **envp_path, char *cmd, char *path_cmd)
{
	char	*path;

	while (envp_path[++i])
	{
		path = ft_strjoin(envp_path[i], "/");
		if (!path)
		{
			ft_free(envp_path);
			error(1, NULL);
		}
		path_cmd = ft_strjoin(path, cmd);
		free(path);
		if (!path_cmd)
		{
			ft_free(envp_path);
			error(1, NULL);
		}
		if (access(path_cmd, F_OK | X_OK) == 0)
		{
			ft_free(envp_path);
			return (path_cmd);
		}
		free(path_cmd);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:01:58 by ctacconi          #+#    #+#             */
/*   Updated: 2024/07/03 15:11:06 by ctacconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../ft_printf/ft_printf.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

# define READ_END	0
# define WRITE_END	1

void	arg_error(void);
void	error(int num_error, char *str);
char	*get_path(char *cmd, char **envp, int i, char *path_cmd);
void	ft_free(char **strs);
void	handle_error(char *argv, char **s_cmd, char *path_cmd, int error_code);
char	*ft_aux(int i, char **envp_path, char *cmd, char *path_cm);

#endif

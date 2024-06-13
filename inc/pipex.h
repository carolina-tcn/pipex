/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinatacconis <carolinatacconis@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:21:30 by ctacconi          #+#    #+#             */
/*   Updated: 2024/06/13 11:26:58 by carolinatac      ###   ########.fr       */
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

# define READ_END   0   //INDEX PIPE EXTREMO LECTURA
# define WRITE_END  1   //INDEX PIPE EXTREMO ESCRITURA

void	arg_error(void);
void	error(int num_error);
char    *get_path(char *cmd, char **envp);
void    ft_free(char	**strs);

#endif
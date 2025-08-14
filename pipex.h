/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-12 17:26:48 by crosorio          #+#    #+#             */
/*   Updated: 2025-08-12 17:26:48 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_data
{
	char	***commands;
	char	**filenames;
	char	**envp;
}			t_data;
// arg_validation.c
int			ft_are_arguments_valid(char **arguments);
int			ft_is_string_empty_or_blank(char *s);
void		ft_store_commands(int arg_size, char **arguments, t_data *data);
void		ft_store_filenames(int arg_size, char **arguments, t_data *data);
// utils.c
void		ft_free_memory(t_data *data, char **paths);
void		ft_free_paths(char **paths);
void		ft_msg_exit(t_data *data, char **paths, char *msg, int exit_code);
void		ft_perror_exit(t_data *data, char **paths, char *prefix,
				int exit_code);
void		ft_handle_execve_error(t_data *data, char *cmd);
// validations.c
char		*ft_get_path(char **envp);
void		ft_validate_commands(t_data *data);
void			ft_command_validation_aux(t_data *data, char **paths);
char		*ft_get_full_path(char *command, char **paths);
// process.c
void		ft_execute_child(t_data *data, int pipe_fd[], char child, int fd);
int		ft_process_aux(int pipe_fd[], t_data *data, int infile_fd,
				int outfile_fd);
int		ft_process(t_data *data);

#endif

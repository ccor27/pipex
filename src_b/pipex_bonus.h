/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:31:39 by crosorio          #+#    #+#             */
/*   Updated: 2025/08/19 20:17:15 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_data
{
	char	***commands;
	char	**cmd_paths;
	int		num_commands;
	char	**filenames;
	char	**envp;
	int		infile;
	int		outfile;
}			t_data;

//error_handler_bonus.c
void	ft_perror_exit(t_data *data, char **paths, char *prefix, int exit_code);
void	ft_command_not_found_exit(t_data *data, char **paths, char *cmd);
void	ft_handle_execve_error(t_data *data, char **paths, char *cmd, int code);
void	ft_msg_exit(t_data *data, char **paths, char *msg, int exit_code);
//arg_validation_bonus.c
int	ft_is_string_empty_or_blank(char *s);
int	ft_are_arguments_valid(char **arguments);
void	ft_store_commands(int arg_size, char **arguments, t_data *data);
void	ft_store_filenames(int arg_size, char **arguments, t_data *data);
//validations_bonus.c
char	*ft_get_path(char **envp);
void	ft_validate_commands(t_data *data);
void	ft_command_validation_aux(t_data *data, char **paths);
char	*ft_get_full_path(char *command, char **paths);
#endif

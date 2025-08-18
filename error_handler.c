/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-17 13:52:13 by crosorio          #+#    #+#             */
/*   Updated: 2025-08-17 13:52:13 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Function to free memory and exit using perror
 * in case of error
 */
void	ft_perror_exit(t_data *data, char **paths, char *prefix, int exit_code)
{
	if (prefix)
		perror(prefix);
	ft_free_memory(data, paths);
	exit(exit_code);
}

/**
 * Function to handle commands not found
 */
void	ft_command_not_found_exit(t_data *data, char **paths, char *cmd)
{
	char	*msg;
	char	*full_msg;

	if (cmd)
	{
		msg = ft_strjoin(cmd, ": command not found\n");
		full_msg = ft_strjoin("pipex: ", msg);
		write(2, full_msg, ft_strlen(full_msg));
		free(msg);
		free(full_msg);
	}
	ft_free_memory(data, paths);
	exit(127);
}

/**
 * Function to hanle error during the execve
 */
void	ft_handle_execve_error(t_data *data, char **paths, char *cmd, int code)
{
	if (code == ENOENT)
		ft_command_not_found_exit(data, paths, cmd);
	else if (code == EACCES)
		ft_perror_exit(data, paths, cmd, 126);
	else
		ft_perror_exit(data, paths, cmd, 1);
}

/**
 * Function to free memory and exit showing a personalized message
 * in case of error
 */
void	ft_msg_exit(t_data *data, char **paths, char *msg, int exit_code)
{
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 2);
	}
	ft_free_memory(data, paths);
	exit(exit_code);
}

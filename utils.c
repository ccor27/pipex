/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-09 12:50:34 by crosorio          #+#    #+#             */
/*   Updated: 2025-08-09 12:50:34 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Function to free memory of the struct
 */
void	ft_free_memory(t_data *data, char **paths)
{
	int	i;
	int	j;

	if (data->filenames)
	{
		free(data->filenames[0]);
		free(data->filenames[1]);
		free(data->filenames);
	}
	i = 0;
	if (data->commands)
	{
		while (data->commands[i])
		{
			j = 0;
			while (data->commands[i][j])
				free(data->commands[i][j++]);
			free(data->commands[i++]);
		}
		free(data->commands);
	}
	if (paths)
		ft_free_paths(paths);
}

/**
 *Function to free the memory of the matrix that
 *contains the paths
 */
void	ft_free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

/**
 * Function to free memory and exit using perror
 * in case of error
 */
void	ft_perror_exit(t_data *data, char **paths, const char *prefix,
		int exit_code)
{
	if (prefix)
		perror(prefix);
	ft_free_memory(data, paths);
	exit(exit_code);
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

/**
 * Function to hanle error during the execve
 */
void	ft_handle_execve_error(t_data *data, char *cmd)
{
	if (errno == ENOENT)
		ft_perror_exit(data, NULL, cmd, 127);
	else if (errno == EACCES)
		ft_perror_exit(data, NULL, cmd, 126);
	else
		ft_perror_exit(data, NULL, cmd, 1);
}

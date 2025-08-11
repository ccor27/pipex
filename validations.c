/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-09 16:23:18 by crosorio          #+#    #+#             */
/*   Updated: 2025-08-09 16:23:18 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Function to get the paths from the
 * environment variables
 */
char	*ft_get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

/**
 * Principal function to validate the commands
 */
int	ft_validate_commands(t_data *data)
{
	char	*path;
	char	**paths;

	path = ft_get_path(data->envp);
	if (!path)
		ft_exit_and_free(data, NULL, "Error, getting the path\n");
	paths = ft_split(path, ':');
	if (!paths)
		ft_exit_and_free(data, NULL, "Error, spliting the paths\n");
	if (!ft_command_validation_aux(data, paths))
		ft_exit_and_free(data, paths, "Error, commands no valid\n");
	ft_free_paths(paths);
	return (1);
}

/**
 * Auxiliary function that validate the commands
 */
int	ft_command_validation_aux(t_data *data, char **paths)
{
	int		i;
	char	*full_path;

	i = 0;
	while (data->commands[i])
	{
		if (data->commands[i][0][0] == '/')
		{
			if (access(data->commands[i][0], X_OK) != 0)
				return (0);
		}
		else
		{
			full_path = ft_get_full_path(data->commands[i][0], paths);
			if (!full_path)
				return (0);
			free(data->commands[i][0]);
			data->commands[i][0] = full_path;
		}
		i++;
	}
	return (1);
}

/**
 * Function to get the full path of the command and
 * validate if it is valid
 */
char	*ft_get_full_path(char *command, char **paths)
{
	int		i;
	char	*full_path;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

/**
 * Function to validate the filenames
 */
void	ft_validate_filenames(t_data *data)
{
	if (access(data->filenames[0], F_OK | R_OK) != 0)
		ft_exit_and_free(data, NULL, "Error,filename either exist or not has the read permissions\n");
	if (access(data->filenames[1], W_OK) != 0)
		ft_exit_and_free(data, NULL, "Error,filename not has the write permission\n");
}

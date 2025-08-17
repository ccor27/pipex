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
void	ft_validate_commands(t_data *data)
{
	char	*path;
	char	**paths;

	path = ft_get_path(data->envp);
	paths = NULL;
	if (path)
	{
		paths = ft_split(path, ':');
		if (!paths)
			ft_msg_exit(data, NULL, "Error: spliting the paths", 1);
	}
	ft_command_validation_aux(data, paths);
	if (paths)
		ft_free_paths(paths);
}

/**
 * Auxiliary function that validate the commands
 */
void	ft_command_validation_aux(t_data *data, char **paths)
{
	int		i;
	char	*full_path;

	i = 0;
	data->cmd_paths = malloc(sizeof(char *) * (data->num_commands + 1));
	if (!data->cmd_paths)
		ft_msg_exit(data, NULL, "Error: reserving memory for commands path", 1);
	while (data->commands[i])
	{
		if (data->commands[i][0][0] == '/')
			data->cmd_paths[i] = ft_strdup(data->commands[i][0]);
		else if (paths)
		{
			full_path = ft_get_full_path(data->commands[i][0], paths);
			if (full_path)
				data->cmd_paths[i] = full_path;
			else
				data->cmd_paths[i] = NULL;
		}
		else
			data->cmd_paths[i] = NULL;
		i++;
	}
	data->cmd_paths[i] = NULL;
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

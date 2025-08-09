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
char *ft_get_path(char **envp)
{
	int i;

	i = 0;
	while(envp[i])
	{
		if(ft_strncmp(envp[i],"PATH=",5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return(NULL);
}

/**
 * Principal function to validate the commands
 */
int ft_validate_commands(t_data *data, char **envp)
{
	char *path;
	char **paths;

	path = ft_get_path(envp);
	if(!path)
		ft_exit_and_free(data,NULL);
	paths = ft_split(path,':');
	if(!paths)
		ft_exit_and_free(data,NULL);
	if(!ft_command_validation_aux(data,paths))
		ft_exit_and_free(data,paths);
	ft_free_paths(paths);
	return(1);
}

/**
 * Auxiliary function that validate the commands
 */
int	ft_command_validation_aux(t_data *data, char **paths)
{
	int i;
	char *full_path;

	i = 0;
	while(data->commands[i])
	{
		if(data->commands[i][0][0]=='/')
		{
			if(access(data->commands[i][0],X_OK) != 0)
				return (0);
		}
		else
		{
			full_path = ft_get_full_path(data->commands[i][0],paths);
			if(!full_path)
				return(0);
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
	int i;
	char *full_path;

	i = 0;
	while(paths[i])
	{
		full_path = ft_strjoin(paths[i],"/");
		full_path = ft_strjoin(full_path,command);
		if(access(full_path,X_OK) == 0)
			return(full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

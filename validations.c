/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:23:18 by crosorio          #+#    #+#             */
/*   Updated: 2025/08/13 21:17:41 by crosorio         ###   ########.fr       */
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
 * 	if (!ft_command_validation_aux(data, paths))
ft_msg_exit(data, paths, "Error: there are  commands no valid", 1);
 */
void	ft_validate_commands(t_data *data)
{
	char	*path;
	char	**paths;

	path = ft_get_path(data->envp);
	if (!path)
		ft_msg_exit(data, NULL, "Error: getting the paths", 1);
	paths = ft_split(path, ':');
	if (!paths)
		ft_msg_exit(data, NULL, "Error: spliting the paths", 1);
	
	ft_command_validation_aux(data, paths);
	//ft_printf("Luego de guardar los paths de los comandos\n");
	ft_free_paths(paths);
}

// void static ft_print_commands(t_data *data)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while(data->commands[i])
// 	{
// 		j = 0;
// 		while (data->commands[i][j])
// 		{
// 			ft_printf("%s\n",data->commands[i][j]);
// 			j++;
// 		}
// 		i++;
// 	}
// }

/**
 * Auxiliary function that validate the commands
 */
void	ft_command_validation_aux(t_data *data, char **paths)
{
	int		i;
	char	*full_path;

	i = 0;
	//ft_print_commands(data);
	while (data->commands[i])
	{
		// ft_printf("antes de llamar ft_get_full_path\n");
		// ft_printf("valor de command: %s\n",data->commands[i][0]);
		full_path = ft_get_full_path(data->commands[i][0], paths);
		//ft_printf("despues de llamar ft_get_full_path\n");
		if (!full_path)
			return;
		data->command_paths[i] = full_path;
		i++;
	}
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
	//ft_printf("antes del while en get_full_path\n");
	while (paths[i])
	{
		//ft_printf("dentro del while en get_full_path (antes del joins\n");
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, command);
		//ft_printf("dentro del while en get_full_path (despues del joins\n");
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	//ft_printf("despues del while en get_full_path\n");
	return (NULL);
}

/**
 * Function to validate the filenames
 */
void	ft_validate_filenames(t_data *data)
{
	if (access(data->filenames[0], F_OK | R_OK) != 0)
		ft_perror_exit(data, NULL, data->filenames[0], 1);
}

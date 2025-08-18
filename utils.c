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
	if (data->cmd_paths)
		ft_free_cmd_paths(data);
}

void	ft_free_cmd_paths(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd_paths[i])
		free(data->cmd_paths[i++]);
	free(data->cmd_paths);
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

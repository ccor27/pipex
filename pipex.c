/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 09:12:39 by crosorio          #+#    #+#             */
/*   Updated: 2025/08/13 19:47:17 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Function to initialize the struct
 */
static void	ft_initialize_data(t_data *data, char **envp)
{
	data->commands = NULL;
	data->filenames = NULL;
	data->envp = envp;
}

/**
 * Main function
 */
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		exit_code;

	ft_initialize_data(&data, envp);
	if (argc < 5)
		ft_msg_exit(&data, NULL, "Usage: ./pipex file1 cmd1 cmd2 file2", 1);
	if (!ft_are_arguments_valid(argv))
		ft_msg_exit(&data, NULL, "Error: arguments no valid", 1);
	ft_store_commands(argc, argv, &data);
	ft_store_filenames(argc, argv, &data);
	ft_validate_commands(&data);
	ft_validate_filenames(&data);
	exit_code = ft_process(&data);
	ft_free_memory(&data, NULL);
	return (exit_code);
}

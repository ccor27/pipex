/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-11 12:31:36 by crosorio          #+#    #+#             */
/*   Updated: 2025-08-11 12:31:36 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * int	ft_process(t_data *data)
{
	int	pipe_fd[2];
	int	infile_fd;
	int	outfile_fd;
	int	status;

	infile_fd = open(data->filenames[0], O_RDONLY);
	if (infile_fd < 0)
	{
		write(2, "pipex: ", 7);
		perror(data->filenames[0]);
		infile_fd = open("/dev/null", O_RDONLY);
	}
	outfile_fd = open(data->filenames[1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (outfile_fd < 0)
	{
		close(infile_fd);
		ft_perror_exit(data, NULL, data->filenames[1], 126);
	}
	status = ft_process_aux(pipe_fd, data, infile_fd, outfile_fd);
	close(infile_fd);
	close(outfile_fd);
	return (status);
}
 */

/**
 * Principal function to make the process of fork and execve
 */

 static pid_t	ft_first_child(t_data *data, int pipe_fd[])
{
	pid_t	p1;

	p1 = fork();
	if (p1 < 0)
		ft_perror_exit(data, NULL, "fork (1)", 1);
	if (p1 == 0)
	{
		data->infile = open(data->filenames[0], O_RDONLY);
		if (data->infile < 0)
			ft_perror_exit(data, NULL, data->filenames[0], 126);
		close(pipe_fd[0]);
		if (dup2(data->infile, STDIN_FILENO) < 0 || dup2(pipe_fd[1],
				STDOUT_FILENO) < 0)
			ft_perror_exit(data, NULL, "dup (1)", 1);
		close(pipe_fd[1]);
		close(data->infile);
		if (data->cmd_paths[0] == NULL)
			ft_handle_execve_error(data, NULL, data->commands[0][0], ENOENT);
		else if (execve(data->cmd_paths[0], data->commands[0], data->envp) ==
			-1)
			ft_handle_execve_error(data, NULL, data->commands[0][0], errno);
	}
	return (p1);
}

static pid_t	ft_second_child(t_data *data, int pipe_fd[])
{
	pid_t	p2;

	p2 = fork();
	if (p2 < 0)
		ft_perror_exit(data, NULL, "fork (2)", 1);
	if (p2 == 0)
	{
		data->outfile = open(data->filenames[1], O_WRONLY | O_CREAT | O_TRUNC,
				0664);
		if (data->outfile < 0)
			ft_perror_exit(data, NULL, data->filenames[1], 126);
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) < 0 || dup2(data->outfile,
				STDOUT_FILENO) < 0)
			ft_perror_exit(data, NULL, "dup (2)", 1);
		close(data->outfile);
		close(pipe_fd[0]);
		if (data->cmd_paths[1] == NULL)
			ft_handle_execve_error(data, NULL, data->commands[1][0], ENOENT);
		else if (execve(data->cmd_paths[1], data->commands[1], data->envp) ==
			-1)
			ft_handle_execve_error(data, NULL, data->commands[1][0], errno);
	}
	return (p2);
}

int	ft_process(t_data *data)
{
	int		pipe_fd[2];
	int		status;
	pid_t	p1;
	pid_t	p2;

	pipe(pipe_fd);
	p1 = ft_first_child(data, pipe_fd);
	p2 = ft_second_child(data, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(p1, NULL, 0);
	waitpid(p2, &status, 0);
	return ((status >> 8) & 0xFF);
}

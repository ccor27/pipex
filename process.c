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
 * Function to execute a child process using exceve and dup2
 */
void	ft_execute_child(t_data *data, int pipe_fd[], char child, int fd)
{
	if (child == '1')
	{
		close(pipe_fd[0]);
		if (dup2(fd, STDIN_FILENO) < 0 || dup2(pipe_fd[1], STDOUT_FILENO) < 0)
			ft_perror_exit(data, NULL, "dup (1)", 1);
		close(fd);
		close(pipe_fd[1]);
		if (execve(data->commands[0][0], data->commands[0], data->envp) == -1)
			ft_handle_execve_error(data, data->commands[0][0]);
	}
	else
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) < 0 || dup2(fd, STDOUT_FILENO) < 0)
			ft_perror_exit(data, NULL, "dup (2)", 1);
		close(fd);
		close(pipe_fd[0]);
		if (execve(data->commands[1][0], data->commands[1], data->envp) == -1)
			ft_handle_execve_error(data, data->commands[1][1]);
	}
}

/**
 *Auxiliary function to make the process of fork, close pipe and wait
 for children are done
 */
void	ft_process_aux(int pipe_fd[], t_data *data, int infile_fd,
		int outfile_fd)
{
	pid_t	p1;
	pid_t	p2;

	pipe(pipe_fd);
	p1 = fork();
	if (p1 < 0)
		ft_perror_exit(data, NULL, "fork (1)", 1);
	if (p1 == 0)
		ft_execute_child(data, pipe_fd, '1', infile_fd);
	p2 = fork();
	if (p2 < 0)
		ft_perror_exit(data, NULL, "fork (2)", 1);
	if (p2 == 0)
		ft_execute_child(data, pipe_fd, '2', outfile_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(p1, NULL, 0);
	waitpid(p2, NULL, 0);
}

/**
 * Principal function to make the process of fork and execve
 */
void	ft_process(t_data *data)
{
	int	pipe_fd[2];
	int	infile_fd;
	int	outfile_fd;

	infile_fd = open(data->filenames[0], O_RDONLY);
	outfile_fd = open(data->filenames[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile_fd < 0)
		ft_perror_exit(data, NULL, data->filenames[0], 1);
	if (outfile_fd < 0)
		ft_perror_exit(data, NULL, data->filenames[1], 1);
	ft_process_aux(pipe_fd, data, infile_fd, outfile_fd);
}


#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
#include <fcntl.h>
#include <sys/wait.h>

typedef struct s_data
{
	char	***commands;
	char	**filenames;
	char	**envp;
}					t_data;
//arg_validation.c
int ft_are_arguments_valid(char **arguments);
int	ft_is_string_empty_or_blank(char *s);
void	ft_store_commands(int arg_size, char **arguments, t_data *data);
void	ft_store_filenames(int arg_size, char **arguments, t_data *data);
//utils.c
void	ft_exit_and_free(t_data *data, char **paths, char *message);
void	ft_free_paths(char **paths);
//validations.c
char *ft_get_path(char **envp);
int ft_validate_commands(t_data *data);
int	ft_command_validation_aux(t_data *data, char **paths);
char	*ft_get_full_path(char *command, char **paths);
void	ft_validate_filenames(t_data *data);
//process.c
void	ft_execute_child(t_data *data, int pipe_fd[], char child, int fd);
void	ft_process(t_data *data);

#endif

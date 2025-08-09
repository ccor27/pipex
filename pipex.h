
#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"

typedef struct s_data
{
	char	***commands;
	char	**filenames;
}					t_data;
//arg_validation.c
int ft_are_arguments_valid(char **arguments);
int	ft_is_string_empty_or_blank(char *s);
void	ft_store_commands(int arg_size, char **arguments, t_data *data);
void	ft_store_filenames(int arg_size, char **arguments, t_data *data);
//utils.c
void	ft_exit_and_free(t_data *data, char **paths);
void	ft_free_paths(char **paths);
//commands_validation.c
char *ft_get_path(char **envp);
int ft_validate_commands(t_data *data, char **envp);
int	ft_command_validation_aux(t_data *data, char **paths);
char	*ft_get_full_path(char *command, char **paths);

#endif

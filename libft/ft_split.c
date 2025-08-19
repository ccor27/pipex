/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:01:54 by crosorio          #+#    #+#             */
/*   Updated: 2025/08/08 21:19:54 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_know_words(char const *s, char c, int in_word_flag, int i)
{
	int		count;
	char	quote;

	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (!in_word_flag)
			{
				count++;
				in_word_flag = 1;
			}
			if (s[i] == '\'' || s[i] == '"')
			{
				quote = s[i++];
				while (s[i] && s[i] != quote)
					i++;
			}
		}
		else
			in_word_flag = 0;
		i++;
	}
	return (count);
}

static int	ft_skip_quotes(const char *s, int i)
{
	char	quote;

	quote = s[i];
	i++;
	while (s[i] && s[i] != quote)
		i++;
	return (i);
}

static char	**ft_fill_up_matrix(const char *s, char c, char **matrix)
{
	int	i;
	int	start;
	int	idx;

	i = 0;
	start = -1;
	idx = 0;
	while (s[i])
	{
		if (s[i] != c && start == -1)
			start = i;
		if (start != -1 && (s[i] == '\'' || s[i] == '"'))
			i = ft_skip_quotes(s, i);
		if (start != -1 && (s[i + 1] == '\0' || s[i + 1] == c))
		{
			matrix[idx++] = ft_substr(s, start, i - start + 1);
			if (!matrix[idx - 1])
				return (NULL);
			start = -1;
		}
		i++;
	}
	matrix[idx] = NULL;
	return (matrix);
}

static char	**ft_handle_special_cases(void)
{
	char	**matrix;

	matrix = malloc(sizeof(char *));
	if (!matrix)
		return (NULL);
	matrix[0] = NULL;
	return (matrix);
}

char	**ft_split(char const *s, char c)
{
	int		num_substrings;
	char	**matrix;
	int		i;

	if (!s)
		return (ft_handle_special_cases());
	num_substrings = ft_know_words(s, c, 0, 0);
	if (num_substrings == 0)
		return (ft_handle_special_cases());
	matrix = malloc((num_substrings + 1) * sizeof(char *));
	if (!matrix)
		return (NULL);
	if (!ft_fill_up_matrix(s, c, matrix))
	{
		i = 0;
		while (matrix[i])
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
		return (NULL);
	}
	return (matrix);
}

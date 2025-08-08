/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:01:54 by crosorio          #+#    #+#             */
/*   Updated: 2025/05/22 16:50:56 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_know_words(char const *s, char c)
{
	int	i;
	int	count;
	int	in_word_flag;

	i = 0;
	count = 0;
	in_word_flag = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (!in_word_flag)
			{
				count++;
				in_word_flag = 1;
			}
		}
		else
			in_word_flag = 0;
		i++;
	}
	return (count);
}

static void	*ft_free_memory(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return (NULL);
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
		if (start != -1 && (s[i + 1] == '\0' || s[i] == c))
		{
			matrix[idx] = ft_substr(s, start, i - start + (s[i] != c));
			if (!matrix[idx])
				return (NULL);
			idx++;
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

	if (!s)
		return (ft_handle_special_cases());
	num_substrings = ft_know_words(s, c);
	if (num_substrings == 0)
		return (ft_handle_special_cases());
	matrix = malloc((num_substrings + 1) * sizeof(char *));
	if (!matrix)
		return (NULL);
	if (!ft_fill_up_matrix(s, c, matrix))
		return (ft_free_memory(matrix));
	return (matrix);
}
/*
word = malloc((i - start + (s[i] != c)) + 1);
			if (!word)
				return (NULL);
			ft_memcpy(word, s + start, i - start + (s[i] != c));
			word[i - start + (s[i] != c)] = '\0';
*/
/*
char	**ft_fill_up_matrix(const char *s, char **matrix, char c, int index)
{
	int		start;
	char	*word;
	int		i;
	int		len;

	i = 0;
	start = -1;
	while (s[i])
	{
		if (s[i] != c && start == -1)
			start = i;
		if (start != -1 && (s[i] == c || s[i + 1] == '\0'))
		{
			if (s[i] == c)
				len = i - start;
			else
				len = i - start + 1;
			word = malloc(len + 1);
			if (!word)
				return (NULL);
			ft_memcpy(word, s + start, len);
			matrix[len] = '\0';
			matrix[index++] = word;
			start = -1;
		}
		i++;
	}
	matrix[index] = NULL;
	return (matrix);
}
*/

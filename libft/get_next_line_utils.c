/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:17:36 by crosorio          #+#    #+#             */
/*   Updated: 2025/08/13 16:19:29 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * libft function to get the pointer of the first character appearance,
 * if it exists in the string.
 * In this case we use this function to know if the
 * character exist int the string
 */
char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}

/**
 * libft function to get a substring from an string
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_lenght;
	size_t	i;
	char	*sub;

	s_lenght = ft_strlen(s);
	i = 0;
	if (start >= s_lenght)
		return (ft_strdup(""));
	if (len > s_lenght - start)
		len = s_lenght - start;
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	while (s[start] && i < len)
	{
		sub[i] = s[start];
		start++;
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

/**
 * libft function to append two string into a new one
 */
char	*ft_strjoin_gnl(char const *s1, char const *s2, size_t i, size_t j)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;

	len1 = 0;
	len2 = 0;
	i = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	while (i < len1)
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len2)
		new_str[i++] = s2[j++];
	new_str[i] = '\0';
	return (new_str);
}

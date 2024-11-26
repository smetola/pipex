/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanmetol <sanmetol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:06:13 by sanmetol          #+#    #+#             */
/*   Updated: 2024/11/26 20:06:14 by sanmetol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_word_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*get_words(char const *s, char c, int *start)
{
	int		end;
	char	*word;
	int		i;

	while (s[*start] == c)
		(*start)++;
	end = *start;
	while (s[end] && s[end] != c)
		end++;
	word = (char *)malloc(sizeof(char) * (end - *start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (*start < end)
		word[i++] = s[(*start)++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**splited;
	int		i;
	int		start;
	int		n_words;

	n_words = get_word_count(s, c);
	splited = (char **)malloc(sizeof(char *) * (n_words + 1));
	if (!splited)
		return (NULL);
	i = 0;
	start = 0;
	while (i < n_words)
	{
		splited[i] = get_words(s, c, &start);
		if (!splited[i])
		{
			while (i > 0)
				free(splited[--i]);
			free(splited);
			return (NULL);
		}
		i++;
	}
	splited[i] = NULL;
	return (splited);
}

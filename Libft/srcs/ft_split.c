/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:15:43 by jalvarad          #+#    #+#             */
/*   Updated: 2021/05/31 17:15:52 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *str, char c)
{
	int	count;
	int	p;

	count = 0;
	p = 0;
	while (*str == c)
		str++;
	if (*str == '\0')
		return (0);
	while (str[p])
	{
		if (str[p] == c && str[p + 1] != c && str[p + 1] != '\0')
			count++;
		p++;
	}
	return (count + 1);
}

static char	*ft_ultimate_memcpy(const char *src, char c)
{
	size_t	i;
	char	*dst;

	i = 0;
	while (src[i] && src[i] != c)
		i++;
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != c)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static void	ft_locate_words(const char *s, char **aux, size_t words, char c)
{
	size_t	cont;
	size_t	cont2;

	cont = 0;
	cont2 = 0;
	while (cont < words)
	{
		while (s[cont2] == c)
			cont2++;
		aux[cont] = ft_ultimate_memcpy(s + cont2, c);
		while (s[cont2] && s[cont2] != c)
			cont2++;
		cont++;
	}
	aux[cont] = NULL;
}

char	**ft_split(const char *s, char c)
{
	size_t	words;
	char	**aux;

	if (!s)
		return (NULL);
	if (*s == 0)
	{
		aux = (char **)malloc(sizeof(char *));
		aux[0] = NULL;
		return (aux);
	}
	words = ft_word_count(s, c);
	aux = (char **)malloc(sizeof(char *) * (words + 1));
	if (!aux)
		return (NULL);
	ft_locate_words(s, aux, words, c);
	return (aux);
}

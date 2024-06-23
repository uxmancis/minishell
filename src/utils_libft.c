/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 20:32:39 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 16:04:57 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] == s2[i])
		{
			i++;
		}
		else
			return ((unsigned char ) s1[i] - (unsigned char) s2[i]);
	}
	return (0);
}

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	size;

	size = ft_strlen(s1);
	dst = malloc (sizeof(char) * (size + 1));
	if (!dst)
		return (0);
	ft_memcpy (dst, s1, size + 1);
	*(dst + size) = '\0';
	return (dst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	s2 = malloc (sizeof(char) * len + 1);
	if (!s2)
		return (0);
	while (len > i && (start + i) < ft_strlen(s))
	{
		s2[i] = s[start + i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*dst;
	unsigned char	*temp;
	size_t			total;

	total = size * count;
	dst = malloc (total);
	if (!dst)
		return (0);
	temp = dst;
	while (total > 0)
	{
		*temp = '\0';
		temp++;
		total--;
	}
	return (dst);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if ((dst == NULL) && (src == NULL))
		return (0);
	while (i < n)
	{
		*(char *)(dst + i) = *(char *) src;
		i++;
		src++;
	}
	return (dst);
}

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') \
			|| (c >= 'A' && c <= 'Z') \
			|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

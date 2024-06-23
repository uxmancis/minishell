/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:19:51 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 16:29:31 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_substr_len(char const *s, char c, int i)
{
	int	start;

	start = i;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i - start);
}

int	count_boxes(char const *s, char c)
{
	int	i;
	int	count_boxes;

	i = 0;
	count_boxes = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			if (s[i] == c || s[i] == '\0')
				count_boxes++;
		}
		if (s[i] != '\0')
			i++;
	}
	return (count_boxes);
}

char	**ft_split2(char const *s, char c, char **dst)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			dst[y] = malloc(sizeof(char) * (ft_substr_len(s, c, i) + 1));
			ft_memcpy(dst[y], (s + i), ft_substr_len(s, c, i));
			dst[y++][ft_substr_len(s, c, i)] = '\0';
		}
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	dst[count_boxes(s, c)] = NULL;
	return (dst);
}

void	fill_boxes(char const *s, char **dst, char c)
{
	int	i;
	int	y;
	int	x;

	i = 0;
	y = 0;
	x = 0;
	while (s[i] != '\0')
	{
		while (s[i] != c)
		{
			dst[x][y] = s[i];
			y++;
			i++;
		}
		while (s[i] == c)
			i++;
		x++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**dst;

	if (!s)
		return (0);
	dst = (char **) malloc (sizeof(char *) * (count_boxes(s, c) + 1));
	if (!dst)
		return (0);
	return (ft_split2(s, c, dst));
}

/*int main(void)
{
	char *s = "kaixoa";
	char c = ' ';
	int a;
	int b;
	char **dst;
//	printf("%d\n", count_boxes (s, c));
//	printf("%d\n", substr_len());
	dst = ft_split(s, c);
	a = 0;
	while(dst[a] != NULL)
	{
		b = 0;
		while(dst[a][b] != '\0')
		{		
			write(1, &dst[a][b], 1);
			b++;
		}
		write(1, "\n", 1);
		a++;	
	}
	return(0);
}*/

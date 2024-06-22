/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 21:49:11 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/07 18:32:05 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	checkchar_end(char const *s1, char const *set)
{
	int	end;
	int	y;

	end = 0;
	while (s1[end] != '\0')
	{
		end++;
	}
	end--;
	while (end > 0)
	{
		y = 0;
		while (set[y] != '\0')
		{
			if (s1[end] != set[y])
				y++;
			else
				break ;
		}
		if (set[y] == '\0')
			break ;
		end--;
	}
	return (end);
}

int	checkchar_start(char const *s1, char const *set)
{
	int	start;
	int	y;

	start = 0;
	while (s1[start] != '\0')
	{
		y = 0;
		while (set[y] != '\0')
		{
			if (s1[start] != set[y])
				y++;
			else
				break ;
		}
		if (set[y] == '\0')
			break ;
		start++;
	}
	return (start);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		i;
	char	*str_result;
	int		start;
	int		end;
	int		size_result;

	end = checkchar_end(s1, set);
	start = checkchar_start(s1, set);
	if (start > end)
		return (ft_strdup(""));
	size_result = (end - start) + 2;
	str_result = malloc(sizeof(char) * size_result);
	if (!str_result)
		return (0);
	i = 0;
	while ((size_result - 1) > 0)
	{
		str_result[i] = s1[start];
		i++;
		start++;
		size_result--;
	}
	str_result[i] = '\0';
	return (str_result);
}

/*int main(void)
{
	char *s1 = "aaaa";
	char *set = "a";

	printf("%s\n", ft_strtrim(s1, set));
//	printf("%d\n", checkchar_start(s1, set));
//	printf("%d\n", checkchar_end(s1, set));
//	printf("prueba s1[18] = %d\n", s1[18]);
	checkchar_start(s1, set);
//	checkchar_end(s1, set);
	return(0);
}*/

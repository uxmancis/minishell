/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:25:42 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/07 18:31:31 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

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

/*int main(void)
{
	char s1[] = "uxue";

	printf("%s\n", strdup(s1));
	printf("%s\n", ft_strdup(s1));
}*/

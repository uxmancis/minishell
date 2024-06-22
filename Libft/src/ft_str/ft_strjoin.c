/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:54:28 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/07 18:31:35 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	size_s1;
	size_t	size_s2;
	size_t	size_s3;

	if (s1 == NULL || s2 == NULL)
		return (0);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	size_s3 = size_s1 + size_s2 + 1;
	s3 = malloc (sizeof(char) * (size_s1 + size_s2 + 1));
	if (!s3)
		return (0);
	ft_strlcpy (s3, s1, size_s1 + 1);
	ft_strlcat ((s3 + size_s1), s2, size_s3);
	*(s3 + size_s1 + size_s2) = '\0';
	return (s3);
}
/*int main(void)
{
	char *str1 = "hello";
	char *str2 = "uxu";

	ft_strjoin(str1, str2);
//	strjoin(str1, str2); no puedo comprobar, "implicit declaration invalid".
//	printf("%s\n", ft_strjoin(str1, str2));
	return(0);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 11:07:24 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/07 18:31:47 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dstsize)
		return (ft_strlen(src));
	i = -1;
	while (src[++i] && i < dstsize -1)
		dst[i] = src[i];
	dst[i] = '\0';
	return (ft_strlen(src));
}

/*int main(void)
{
	char dst[100] = "Hola me xa";
	char src[] = "llamo Uxue";
	size_t dstsize = ft_strlen(dst);
	
//	printf("%d", ft_strlen(dst));
	ft_strlcpy(dst, src, dstsize);
	return(0);
}*/

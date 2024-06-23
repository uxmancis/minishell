/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:52:36 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 20:36:25 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	total_len;
	int		z;
	size_t	srclen;
	size_t	dstlen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	total_len = dstlen + srclen;
	if (dstlen >= dstsize)
		return (srclen + dstsize);
	z = 0;
	while ((src[z] != '\0') && dstlen < (dstsize -1))
	{
		dst[dstlen] = src[z];
		dstlen++;
		z++;
	}
	dst[dstlen] = '\0';
	return (total_len);
}
/*
int	main(void)
{
	char dest[30]; memset(dest, 0, 30);
	char * src = (char *)"AAAAAAAAA";
	memset(dest, 'C', 5);


	printf("%d\n", ft_strlcat(dest, src, -1));
	printf("%s\n", dest);
	return(0);
}*/

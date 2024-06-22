/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 06:33:30 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/07 18:18:27 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

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
/*int main (void)
{
	char dst[] = "Start";
	char src[] = "stop";
	size_t n = 3;

//	memcpy(dst, src, n);
	ft_memcpy(dst, src, n);
	printf("%s\n", dst);
	return(dst);
}*/

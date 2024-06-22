/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 19:27:30 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/07 18:18:22 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		if (((unsigned char *) s)[i] == (unsigned char) c)
			return ((unsigned char *) s + i);
		i++;
		n--;
	}
	return (0);
}
/*int main(void)
{
	char s[] = "uxue"; 
	int c = 'x';

//	printf("%s\n", memchr(s, c, 1));
	printf("%s\n", ft_memchr(s, c, 3));
	return(0);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 13:40:57 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 20:34:29 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	void	*tmp;

	tmp = b;
	while (len > 0)
	{
		*(unsigned char *) b = (unsigned char) c;
		b++;
		len--;
	}
	return (tmp);
}
/*int main(void)
{
	void *b = strdup("holaquease");
//	char *nuevo_b;
	int c = 'A';
	size_t len = 2;

//	nuevo_b = malloc(sizeof(char) * 21);
//	printf("%s\n", memset(nuevo_b, c, len));
	printf("%s\n", ft_memset(b, c, len));
	return(0);
}*/

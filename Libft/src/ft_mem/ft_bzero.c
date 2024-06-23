/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 13:40:57 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 16:32:59 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_bzero(void *s, size_t len)
{
	while (len > 0)
	{
		*(unsigned char *) s = '\0';
		s++;
		len--;
	}
}
/*int main(void)
{
	void *b = strdup("holaquease");
//	char *nuevo_b;
	int c = '\0';
	size_t len = 2;

//	nuevo_b = malloc(sizeof(char) * 21);
//	printf("%s\n", memset(nuevo_b, c, len));
	printf("%s\n", ft_memset(b, c, len));
	return(0);
}*/

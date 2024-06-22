/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:26:06 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/02 11:38:27 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_isalnum(int c)
{
	printf("ft_isalnum barruan\n");
	if ((c >= 'a' && c <= 'z') \
			|| (c >= 'A' && c <= 'Z') \
			|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

/*int	main(void)
{
	int	c;

	c = '7';
	ft_isalnum (c);
	return (0);
	idea para ft_isalnum(int c) a preguntar a alguien:
	if (ft_isalnum(c) = 1 && ft_isdigit(c) = 1)
		return(1)
	return(0);
}*/

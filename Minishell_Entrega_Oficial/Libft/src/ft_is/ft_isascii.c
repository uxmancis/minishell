/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:35:05 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/09 09:07:33 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/*ft_isascii
*
*	Returns: 
+		1: YES is ascii = se cumple la condición (c >= 0 && c <= 0177)
*		0: NOT ascii
*/
int	ft_isascii(int c)
{
	return (c >= 0 && c <= 0177);
}

/*int main(void)
{
	int c; 
	
	c = 300;
	ft_isascii (c);
	return(0);
}*/

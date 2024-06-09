/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:52:53 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/09 08:42:36 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	//printf("ft_strlen, str = '%s'\n", str);
	while (str[i] != '\0')
	{
		//printf(">>> str[%d] = %c\n", (int)i, str[i]);
		i++;
	}
	//printf("ft_strlen result, counter = %d\n", (int)i);
	return (i);
}
/*int main(void)
{
	char str[] = "holaquease";
	ft_strlen(str);
	return(0);
}*/

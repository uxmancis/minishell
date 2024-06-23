/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:16:54 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 20:36:48 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_nodivisions(int n)
{
	int	i;

	i = 0;
	while (1)
	{
		n = n / 10;
		i++;
		if (n == 0)
			break ;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str_result;
	int		size;
	long	number;

	number = n;
	size = ft_nodivisions(number) + 1;
	if (number < 0)
		size++;
	str_result = malloc(sizeof(char) * size);
	if (!str_result)
		return (0);
	if (number < 0)
	{
		str_result[0] = '-';
		number *= -1;
	}
	str_result[--size] = '\0';
	while (1)
	{
		str_result[size-- - 1] = (number % 10) + '0';
		number /= 10;
		if (number == 0)
			break ;
	}
	return (str_result);
}
/*
int	main(void)
{
	int n = 9;
	
	printf("%s\n", ft_itoa(n));
	return(0);
}
*/

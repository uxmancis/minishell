/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:39:53 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/07 18:31:53 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/*char change_content (unsigned int i, char *str1)
{
	return(str1[i] + 1);
}*/

char	*ft_strmapi(char const *str1, char (*f)(unsigned int, char))
{
	int		i;
	char	*str_result;

	str_result = malloc(sizeof(char) * (ft_strlen(str1) + 1));
	if (!str_result)
		return (0);
	i = 0;
	while (str1[i] != '\0')
	{
		str_result[i] = (char) f(i, (char) str1[i]);
		i++;
	}
	str_result[i] = '\0';
	return (str_result);
}
/*int main(void)
{
	char *str1 = "0123";
	
	printf("%s\n", ft_strmapi(str1, change_content));
	return(0);
}*/

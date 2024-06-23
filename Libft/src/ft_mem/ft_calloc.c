/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:14:18 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 16:32:35 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*dst;
	unsigned char	*temp;
	size_t			total;

	total = size * count;
	dst = malloc (total);
	if (!dst)
		return (0);
	temp = dst;
	while (total > 0)
	{
		*temp = '\0';
		temp++;
		total--;
	}
	return (dst);
}

/*int main(void)
{
	size_t mem_size;
	size_t str_size;
	char *str = "uxu";


	str_size = ft_strlen(str);
	printf("%s", ft_calloc(str_size, sizeof(char)));
}*/

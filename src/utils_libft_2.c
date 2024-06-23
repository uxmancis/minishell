/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:56:52 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 22:58:56 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') \
			|| (c >= 'A' && c <= 'Z') \
			|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

// void	ft_putstr(char *str)
// {
// 	printf("%s", str);
// }

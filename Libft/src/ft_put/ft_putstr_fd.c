/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 12:11:54 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/22 14:56:44 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_putstr_fd(char *str, int fd)
{
	int	count;

	count = 0;
	if (!str)
		return (write(fd, "(null)", 6));
	while (*str)
	{
		count += ft_putchar_fd(*str, fd);
		str++;
	}
	return (count);
}
/*int main(void)
{
	char *s = "uxue";

	ft_putstr_fd(s, 1); //fd file descriptor -->, 0, 1 o 2. 
	return(0);
}*/

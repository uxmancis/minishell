/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:04:48 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/26 17:05:25 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int ft_isspace(int c)
// {
// 	if (c == ' ' || c == '\t' || c == '\n'
//	|| c == '\r' || c == '\f' || c == '\v')
// 		return (1);
//     return (0);
// }

// /* DESCRIPTION:
// Outputs the char c to the file descriptor fd.
// The function returns the number of characters printed and
//	-1 if fails to print.
// ----------------------------------------------------------
//	------------------ */
int	ft_putchar_fd(int c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

/* DESCRIPTION:
Outputs the string s to the file descriptor fd.
The function returns the number of characters printed and -1 if fails to print.
---------------------------------------------------------------------------- */
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

size_t	ft_strcpyy_2(char *dst, const char *src)
{
	size_t	i;
	char	*pt_src;

	pt_src = (char *)src;
	i = 0;
	while (pt_src[i] != '\0')
	{
		{
			dst[i] = pt_src[i];
			i++;
		}
		dst[i] = 0;
	}
	while (src[i])
		i++;
	return (i);
}

char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (*(dest + i))
		i++;
	while (*src)
		*(dest + i++) = *src++;
	*(dest + i) = '\0';
	return (dest);
}

//Fuction to find the position of the equal sign
//while (*(str + i)) //loop to iterate over the string "str"
//for the length of the string
//Returns (i): // If the character at position "i" is equal
// //to the character "c" return the position "i"
// int	ft_sstrncmp(char *str, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (*(str + i))
// 	{
// 		if (*(str + i) == c)
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

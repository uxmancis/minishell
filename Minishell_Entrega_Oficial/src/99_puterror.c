/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 21:15:12 by uxmancis          #+#    #+#             */
/*   Updated: 2024/04/29 21:15:12 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void ft_puterror_exit(char *str)
{
	ft_putstr_fd("\033[31mError: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\033[0;39m", 2);
	exit(EXIT_FAILURE);
}

void ft_puterror(char *str)
{
	ft_putstr_fd("\033[31mError: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\033[0;39m", 2);
}
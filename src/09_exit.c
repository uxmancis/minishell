/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 03:19:28 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/23 20:30:32 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_exit_builtin(t_prompt *prompt, int status)
{
	ft_free_prompt(prompt);
	prompt = NULL;
	rl_clear_history();
	exit(status);
}

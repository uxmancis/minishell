/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_initialize_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:02:43 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/01 13:21:42 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_cmd clean_cmd_init(void)
{
    t_cmd cmd_data;

	cmd_data.nb_substr = -1;
	cmd_data.command = NULL;
	cmd_data.heredoc = 0;
	cmd_data.fd_in = -1;
	cmd_data.fd_out = -1;
	// cmd_data.pipefd = NULL;
	cmd_data.nb_cmds = 0;
	cmd_data.child = -1;
	cmd_data.pids = NULL;
    // cmd_data.parent_pid = NULL;
	// cmd_data.cmd_options = NULL;
	cmd_data.cmd_path = NULL;
    return (cmd_data);
}


t_cmd init_cmd(t_box *box, t_prompt *data, int sub_box_id)
{
    t_cmd cmd_data;
    (void)sub_box_id;

    cmd_data = clean_cmd_init();
    cmd_data.nb_substr = data->nb_of_substr;
    cmd_data.command = box->rest_info_potential_cmd;
    if (box->nb_of_heredocs > 0)
        cmd_data.heredoc = 1;
    handle_redirects(&box, &cmd_data);
    cmd_data.nb_cmds = data->nb_of_substr - data->nb_of_pipes;
    cmd_data.pids = malloc(sizeof *cmd_data.pids * cmd_data.nb_cmds);

    if (create_pipes(&cmd_data) == -1)
	{
		perror("Error create_pipes");
	}
    // printf("           Command ✅"RESET_COLOR GREEN "[  %s  ] \n", cmd_data.command[0]);
    printf(WHITE"           nb_cmd ✅"RESET_COLOR BLUE" [%d] \n", cmd_data.nb_cmds);
    printf(BLUE "       handle_input_infile | "  RED RESET_COLOR MAGENTA"data->infd: "  GREEN "%d\n" , cmd_data.fd_in);
	printf(BLUE "       handle_input_outfile | "  RED RESET_COLOR MAGENTA"data->out: "  GREEN "%d\n" , cmd_data.fd_out);
return (cmd_data);  
    
}

int initialize_cmd(t_box *box, t_prompt *data, int substr_box_id)
{
    t_cmd cmd_data;
    (void)cmd_data;
    int     exit_code;
    printf(RED"           BOX_NB BOXES  "RESET_COLOR GREEN "[%d] \n", substr_box_id);
    printf(YELLOW"              Initialize_cmd\n    "RESET_COLOR);
    cmd_data = init_cmd(box, data, substr_box_id);
    exit_code = create_child_process(&cmd_data, data, &box);
    return (exit_code);
    return (0);     
}





























































































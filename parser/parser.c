/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienkroger <julienkroger@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:08:45 by jkroger           #+#    #+#             */
/*   Updated: 2025/03/22 15:53:45 by julienkroge      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_string_array(char **arr)
{
    if (!arr)
        return;
    for (int i = 0; arr[i] != NULL; i++)
    {
        printf("    [%d]: %s\n", i, arr[i]);
    }
}

char    *and_op_loop(char *input)
{
	char    *tmp_input;

    char    *trim_input;

    tmp_input = readline("> ");
	while (tmp_input && g_exit_status != 130)
	{
		//check errors
        input = ft_strjoin(input, tmp_input); //check mem leaks
        // input = edited_strjoin(input, tmp_input);
        if (!lex_error_check(tmp_input)) 
        {
            free(tmp_input);
            tmp_input = NULL;
            return input; // set err code
        }
        // free input


		free(tmp_input);
        tmp_input = NULL;


        trim_input = ft_strtrim(input, " \t\n");
        if((trim_input[ft_strlen(trim_input) - 1] == '&' 
            && trim_input[ft_strlen(trim_input) - 2] == '&')
            || trim_input[ft_strlen(trim_input) - 1] == '|')
            tmp_input = readline("> ");
        free(trim_input);
	}

	free(tmp_input);
    return input;
}
char    *check_for_open_and(char *input)
{
    char    *trim_input;

    g_exit_status = 0;
    trim_input = ft_strtrim(input, " \t\n");
       
    if((trim_input[ft_strlen(trim_input) - 1] == '&' 
        && trim_input[ft_strlen(trim_input) - 2] == '&')
        || trim_input[ft_strlen(trim_input) - 1] == '|')
        input =  and_op_loop(input);
    

    free(trim_input);

    return (input);
}

t_cmds	*parse(t_cmds *cmd_lst, char **input, char **envp)
{
	t_tokens	*token_lst;
    int         prev_exit_status;

	token_lst = NULL;
	if (!lex_error_check(*input))
	{
		cmd_lst->err = -2;
		return (cmd_lst);
	}


    prev_exit_status = g_exit_status;
    *input = check_for_open_and(*input);

    if (g_exit_status == 2 || g_exit_status == 130) // check mem leaks
    {
        cmd_lst->err = -2;
		return (cmd_lst);
    }
        //handle error free etc.
    
	
    g_exit_status = prev_exit_status;
	token_lst = lexer(token_lst, *input, envp);


    g_exit_status = 0;
	if (init_cmd_struct(&token_lst, &cmd_lst, envp) != 1)
    cmd_lst->err = -2;	


	// t_cmds *current = cmd_lst;
    // // int cmd_index = 0;
   
    // while (current)
    // {
    //     // printf("Command %d:\n", cmd_index++);
        
    //     // // Print cmd_split array if it exists
    //     // if (current->cmd_split)
    //     // {
    //     //     printf("  cmd_split:\n");
    //     //     print_string_array(current->cmd_split);
    //     // }
    //     // else
    //     //     printf("  cmd_split: NULL\n");

    //     // // Print cmd_path
    //     // printf("  cmd_path: %s\n", current->cmd_path ? current->cmd_path : "NULL");
        
    //     // // Print infile and outfile
    //     // printf("  infile: %d\n", current->infile);
    //     // printf("  outfile: %d\n", current->outfile);
        
    //     // // Print err_file
    //     // printf("  err_file: %s\n", current->err_file ? current->err_file : "NULL");
        
    //     // // Print err and prev
    //     // printf("  err: %d\n", current->err);
    //     // printf("  prev: %d\n", current->prev);
        
    //     // // Print env array if it exists
    //     // // if (current->env)
    //     // // {
    //     // //     printf("  env:\n");
    //     // //     print_string_array(current->env);
    //     // // }
    //     // // else
    //     // //     printf("  env: NULL\n");

    //     // // Print var_lst array if it exists
    //     // if (current->var_lst)
    //     // {
    //     //     printf("  var_lst:\n");
    //     //     print_string_array(current->var_lst);
    //     // }
    //     // else
    //     //     printf("  var_lst: NULL\n");
		 
		
        
        
    //     printf("  log_op: %i\n", current->log_op);
    //     printf("  para num: %i\n", current->para_num);

    
    //     printf("\n");
    //     current = current->next;
    // }




	return (cmd_lst);
}

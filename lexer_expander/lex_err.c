/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:45:26 by jkroger           #+#    #+#             */
/*   Updated: 2023/03/12 00:34:30 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_spaces(char *input)
{
	int	i;

	i = -1;
	while (input[++i] != '\0')
	{
		if (input[i] != ' ')
			return (1);
	}
	return (0);
}

int	check_unclosed_quotes(char *input)
{
	int	i;
	int	j;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			j = i + 1;
			while (input[j] && input[j] != input[i])
				j++;
			if (!input[j])
			{
				lex_error("unclosed quotes");
				return (0);
			}
			i = j;
		}
	}
	return (1);
}

int	check_or(char *input, int i)
{
	if (input[++i] == '|')
		i++;
	while (input[i] == ' ')
		i++;
	if (input[i] == '|' || input[i] == '&' || input[i] == ')')
	{
		if (input[i] == '&')
			lex_error( input[i + 1] == '&' ? "&&" : "&");
		else if (input[i] == ')')
			lex_error(")");
		else
			lex_error(((input[i - 1] == '|' &&  input[i]) || (input[i] && input[i + 1] == '|')) ? "||" : "|");
		return (-1);
	}
	return (i);
}

int	check_and(char *input, int i)
{
	if (input[++i] == '&')
		i++;
	else if (input[i] != '|')
	{
		lex_error("&");
		return (-1);
	}
	while (input[i] == ' ')
		i++;
	if (input[i] == '|' || input[i] == '&' || input[i] == ')')
	{
		if (input[i] == '&')
			lex_error( input[i + 1] == '&' ? "&&" : "&");
		else if (input[i] == ')')
			lex_error(")");
		else
			lex_error( input[i + 1] == '|' ? "||" : "|");
		return (-1);
	}
	return (i);
}

int	check_log_op_2(char *input, int i)
{
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			quote_len(input, &i);
		if (input[i] == '|')
			i = check_or(input, i); //if i 0
		else if (input[i] == '&')
			i = check_and(input, i);
		if (i == -1)
			return (0);
		i++;
	}
	return (1);
}

int	check_log_op(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '|')
	{
		if (input[i + 1] == '|')
			lex_error("||");
		else
			lex_error("|");
		return (0);
	}
	else if (input[i] == '&')
	{
		if (input[i + 1] == '&')
			lex_error("&&");
		else
			lex_error("&");
		return (0);
	}
	if (check_log_op_2(input, i) == 0)
		return (0);
	return (1);
}

int	check_unclosed_parenthesis(char *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i] == ' ')
		i++;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			quote_len(input, &i);
		if (input[i] == '(')
		{
			j = i + 1;
			while (input[i] && input[i] != ')')
			{
				if (input[i] == '\'' || input[i] == '"')
					quote_len(input, &i);
				i++;
			}
			while (input[j] && input[j] == ' ')
				j++;
			if (!input[i])
			{
				lex_error("(");
				return (0);
			}
			else if (input[i - 1] == '(' || input[j] == ')')
			{
				lex_error(")");
				return (0);
			}
		}
		else if (input[i] == ')')
		{
			lex_error(")");
			return (0);
		}
		i++;
	}
	return (1);
}

int	lex_error_check(char *input)
{
	if (!check_spaces(input))
		return (0);
	else if (!check_unclosed_quotes(input))
		return (0);
	else if (!check_unclosed_parenthesis(input))
		return (0);
	else if (!check_redir(input))
		return (0);
	else if (!check_log_op(input))
		return (0);
	return (1);
}

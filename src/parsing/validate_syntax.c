/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 05:13:15 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/16 05:33:02 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_semicolons(char *str, int i, t_all *all)
{
	skip_space(i, str);
	if (str[i] == ';')
	{
		error_message("syntax error near unexpected token `;;\'", all);
		return (0);
	}
	else if (str[i] == ';' || i == 1)
	{
		error_message("syntax error near unexpected token `;\'", all);
		return (0);
	}
	return (1);
}

int	check_redirect_in_file(char *str, int i, t_all *all)
{
	int		flag;
	char	*error;
	char	error_symb[2];

	skip_space(i, str);
	if (str[i] == '\n' || str[i] == '\0' || str[i] == '#')
	{
		error_message("syntax error near unexpected token `newline\'", all);
		return (0);
	}
	if (ft_strchr(";<>|()", str[i]))
	{
		error_symb[0] = *ft_strchr(";<>|()", str[i]);
		error_symb[1] = '\'';
		error = ft_strjoin("syntax error near unexpected token `", error_symb);
		error_message(error, all);
		return (0);
	}
	return (1);
}

int	check_redirect_from_file(char *str, int i, t_all *all)
{
	int		flag;
	char	*error;
	char	error_symb[2];

	flag = 0;
	if (str[i] == ' ')
		flag = 1;
	skip_space(i, str);
	if (str[i] == '\n' || str[i] == '\0' || str[i] == '#')
	{
		error_message("syntax error near unexpected token `newline\'", all);
		return (0);
	}
	if (ft_strchr(";<>|()", str[i]))
	{
		error_symb[0] = *ft_strchr(";<>|()", str[i]);
		error_symb[1] = '\'';
		error = ft_strjoin("syntax error near unexpected token `", error_symb);
		if (error_symb[0] == '>' && flag == 0)
			return (1);
		error_message(error, all);
		return (0);
	}
	return (1);
}

int	check_pipe(char *str, int i, t_all *all)
{
	int		flag;
	char	*error;
	char	error_symb[2];

	skip_space(i, str);
	if (str[i] == '\n' || str[i] == '\0' || str[i] == '#')
	{
		error_message("syntax error near unexpected token `newline\'", all);
		return (0);
	}
	if (ft_strchr(";|()", str[i]))
	{
		error_symb[0] = *ft_strchr(";|()", str[i]);
		error_symb[1] = '\'';
		error = ft_strjoin("syntax error near unexpected token `", error_symb);
		if (error_symb[0] == '>' && flag == 0)
			return (1);
		error_message(error, all);
		return (0);
	}
	return (1);
}

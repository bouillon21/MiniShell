/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:40:59 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/16 05:07:01 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ПОЧИНИТЬ DELETE.
*/

void	refresh_cursor(t_all *all, int pos)
{
	all->cursor.start_pos = 0;
	all->cursor.end_pos = pos;
	all->cursor.current_pos = pos;
}

void	insert_inside(char *str, int pos, t_all *all, int flag)
{
	char	*tmp;
	char	*tmp2;
	int		ret_cursor;

	if (pos < 0)
		pos = 0;
	tmp = ft_substr(all->string, 0, pos);
	tmp2 = ft_substr(all->string, pos, ft_strlen(all->string));
	free(all->string);
	all->string = ft_strjoin(tmp, str);
	free(tmp);
	tmp = all->string;
	all->string = ft_strjoin(all->string, tmp2);
	free(tmp);
	free(tmp2);
	if (flag)
	{
		tputs(tigetstr("rc"), 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		write(1, all->string, ft_strlen(all->string));
		ret_cursor = ft_strlen(all->string) - pos - 1;
		while (ret_cursor-- > 0)
		tputs(tgetstr("le", 0), 1, ft_putchar);
	}
}

void	build_string(t_all *all, char *str)
{
	char *tmp;
	int len;

	len = ft_strlen(str);
	all->cursor.end_pos += write(1, str, len);
	all->cursor.current_pos += len;
	if (all->cursor.current_pos != all->cursor.end_pos)
		insert_inside(str, all->cursor.current_pos - len, all, 1);
	else
	{
		tmp = all->string;
		all->string = ft_strjoin(all->string, str);
		free(tmp);
	}
	if (all->flag == 0)
	{
		free(all->old_string);
		all->old_string = ft_strdup(all->string);
	}
}

void	add_history(t_all *all)
{
	char *tmp;

	if (all->string[ft_strlen(all->string) - 1] != '\n')
	{
		tmp = all->string;
		all->string = ft_strjoin(all->string, "\n");
		free(tmp);
	}
	write(all->fd, all->string, ft_strlen(all->string));
	if (all->hist->next)
		while (all->hist->next)
			all->hist = all->hist->next;
	all->hist->string = ft_strdup(all->string);
	if (!all->hist->next)
		all->hist->next = create_new_list(all->hist);
	all->hist = all->hist->next;
}

void	manager_cmd(t_all *all)
{
	if (ft_strcmp(all->token->command, "env") == 0)
		printf_env(all);
	else if (ft_strcmp(all->token->command, "export") == 0)
		export(all);
	else if (ft_strcmp(all->token->command, "cd") == 0)
		cd(all);
	else if (ft_strcmp(all->token->command, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(all->token->command, "unset") == 0)
		ft_uset(all);
	else if (ft_strcmp(all->token->command, "exit") == 0)
		exit (1);
	else
		exec(all);
}

void	launch_command(t_all *all)
{
	t_token		*head;

	head = all->token;
	add_history(all);
	if (parse_string(all))
	{
		all->token = head;
		while(all->token->next)
		{
			if (all->token->command)		// КОСТЫЛЬ ОТ БУЛКИ :)
			{
				ft_pipe(all);
				manager_cmd(all);
			}
			all->token = all->token->next;
		}
	}
	clear_token(all);
	all->flag = 0;
	free(all->string);
}

void	read_input(t_all *all)
{
	char	*str;

	while(1)
	{
		str = ft_calloc(4096, 1);
		read(0, str, 100);
		if (!check_key(str, all))
			build_string(all, str);
		if (ft_strchr(str, '\n'))
		{
			clear_buf(&str);
			break ;
		}
		clear_buf(&str);
	}
}

void	main_loop(t_all *all)
{
	while (1)
	{
		terminal(all);
		refresh_cursor(all, 0);
		write_minishell();
		all->string = ft_calloc(100, 1);
		if (!all->string)
			exit (errno);
		all->string[0] = 0;
		all->old_string = ft_calloc(100, 1);
		read_input(all);
		write(1, "\n", 1);
		free(all->old_string);
		if (all->string[0] != 0)
			launch_command(all);
		else
			clear_buf(&all->string);
	}
}
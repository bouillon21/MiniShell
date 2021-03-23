/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:17:10 by hmickey           #+#    #+#             */
/*   Updated: 2021/03/23 18:16:34 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static int get_capability(const char* label, const char* name, const char** pptr, char** p_buf_ptr)
{
	const char* ptr;

	ptr = tgetstr(name, p_buf_ptr);

	printf("%-22s (%s) = ", label, name);
	print_text(ptr);
	printf("\n");

	*pptr = ptr;
	return ptr != NULL;
}

int main(int argc, char **argv, char **envp)
{
	t_term	term;

	term.termtype = getenv("minishell");
	term.tgetent = tgetent(term.termbuf, term.termtype);
	lines   = tgetnum("li");
	columns = tgetnum("co");

	
	
	printf("lines   (li) = %d\n", lines);	// высота терминала
	printf("columns   (co) = %d\n", columns);	 // ширина терминала
}


//gcc main.c -ltermcap
// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/03/23 13:17:10 by hmickey           #+#    #+#             */
// /*   Updated: 2021/03/24 09:53:36 by hmickey          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "test.h"

void	*fail(int pizda)
{
	printf("%s\n", "PIZDEC\n");
	exit (0);
	return (0);
}

void	test(char *b)
{
	char	*a;
	
	if (a[1] == '1')
		write(1, "1", 1);
	else
		write(1, "2", 1);
}

void handle_sigint(int sig)
{
    printf("exit\n");
	exit(0);
}

int main(int argc, char **argv, char **envp)
{
	t_term	term;

	int len;
	char	symb;

	symb = ' ';
	char	str[1024];
	int i;

	i = 0;
	struct termios	terminal;
	tcgetattr(0, &terminal);
	terminal.c_lflag &= ~(ECHO);
	terminal.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &terminal);
	term.termtype = getenv("xterm-256color");
	term.tgetent = tgetent(term.termbuf, term.termtype);
	signal(SIGINT, handle_sigint);
	while(symb != '\n')
	{
		read(0, &symb, 1);
		write(0, &symb, 1);
		str[i++] = symb;
	}
	printf("%s\n", str);
}
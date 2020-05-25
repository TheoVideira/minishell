#include <minishell.h>

void handle_sigint(int sig)
{
	(void) sig;
	brutally_murder_childrens(sig);
	mini.lastcall = 130;
	// write(1, "\n", 1);
	write(1, "\n\e[1;35mOK-BOOMER\e[0m$>", 24);

}

void handle_sigquit(int sig)
{
	(void) sig;
	brutally_murder_childrens(sig);
	mini.lastcall = 131;
}

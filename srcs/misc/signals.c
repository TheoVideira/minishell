#include <minishell.h>

void handle_sigint(int sig)
{
	(void) sig;
	brutally_murder_childrens();
	write(1, "\n\e[1;35mOK-BOOMER\e[0m$>", 24);
}
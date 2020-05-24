#include <minishell.h>

void handle_sigint(int sig)
{
	(void) sig;
	brutally_murder_childrens();
	write(1, "\n", 1);
}

void handle_sigquit(int sig)
{
	(void) sig;
}

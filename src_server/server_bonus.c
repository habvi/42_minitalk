#include <unistd.h> // pause
#include <stdlib.h> // EXIT_SUCCESS
#include "put.h"
#include "error.h"
#include "server.h"

t_signal	g_signal = {.signum = 0, .client_pid = 0};

t_signal	get_g_signal(void)
{
	return (g_signal);
}

void	set_g_signum(sig_atomic_t signum)
{
	g_signal.signum = signum;
}

void	set_g_client_pid(sig_atomic_t client_pid)
{
	g_signal.client_pid = client_pid;
}

static bool	wait_message_from_client(t_error_code *error_code)
{
	while (true)
	{
		pause();
		if (!recieve_message(error_code))
			return (false);
	}
	return (true);
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;
	t_error_code		error_code;

	error_code = 0;
	(void)argv;
	if (!is_valid_args(argc, &error_code))
		error_exit(error_code);
	if (!put_server_pid(&error_code))
		error_exit(error_code);
	if (!set_sigaction(&sa, &error_code))
		error_exit(error_code);
	if (!wait_message_from_client(&error_code))
		error_exit(error_code);
	return (EXIT_SUCCESS);
}

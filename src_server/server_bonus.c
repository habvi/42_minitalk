#include <unistd.h> // pause
#include <stdlib.h> // EXIT_SUCCESS
#include <stdbool.h>
#include "error.h"
#include "server.h"

t_signal	g_signal = {.signum = 0, .client_pid = 0};

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

int	main(void)
{
	struct sigaction	sa;
	t_error_code		error_code;

	error_code = 0;
	if (!put_server_pid(&error_code))
		error_exit(error_code);
	if (!set_sigaction(&sa, &error_code))
		error_exit(error_code);
	if (!wait_message_from_client(&error_code))
		error_exit(error_code);
	return (EXIT_SUCCESS);
}

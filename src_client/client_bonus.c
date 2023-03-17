#include <stdlib.h> // EXIT_SUCCESS
#include "client.h"
#include "error.h"

t_pid	g_pid = {.server_pid = 0, .is_correct_server_pid = 0};

t_pid	get_g_pid(void)
{
	return (g_pid);
}
void	set_g_is_correct_server_pid(sig_atomic_t is_correct_server_pid)
{
	g_pid.is_correct_server_pid = is_correct_server_pid;
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;
	t_error_code		error_code;
	pid_t				server_pid;

	error_code = 0;
	if (!is_valid_args(argc, &error_code))
		error_exit(error_code);
	if (!is_valid_pid(argv[1], &server_pid, &error_code))
		error_exit(error_code);
	g_pid.server_pid = server_pid;
	if (!set_sigaction(&sa, &error_code))
		error_exit(error_code);
	if (!send_message(g_pid.server_pid, argv[2], &error_code))
		error_exit(error_code);
	if (!recieve_end_signal(&error_code))
		error_exit(error_code);
	return (EXIT_SUCCESS);
}

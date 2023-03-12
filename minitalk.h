#ifndef MINITALK_H
# define MINITALK_H

# define ERROR                  -1
# define ERROR_MSG_WRITE		"Error: function write"

// server.c
# define ERROR_MSG_SIGACTION	"Error: sigaction"

// client.c
# define MSG_USAGE              "usage: ./client <PID> <message>"
// # define MSG_SEND_PID           "send message to pid:"
# define ERROR_MSG_ARGS			"Error: invalid args"
# define ERROR_MSG_PID			"Error: invalid pid"
# define ERROR_MSG_KILL			"Error: kill"

typedef struct t_signal
{
	volatile sig_atomic_t	signum;
	volatile sig_atomic_t	client_pid;
}	s_signal;

// error.c
int     error_exit(const char *error_message);

// put_stderr.c
// void	put_str_to_stderr(const char *str);
// void	put_int_to_stderr(const int num);
void	put_str_int_to_stderr(const char *str, const int num);

#endif

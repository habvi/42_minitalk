#ifndef MINITALK_H
# define MINITALK_H

# define ERROR                  -1
# define ERROR_MSG_WRITE		"Error: function write"

// server.c
# define ERROR_MSG_SIGACTION	"Error: sigaction"

// client.c
# define ERROR_MSG_ARGS			"Error: invalid args"
# define ERROR_MSG_PID			"Error: invalid pid"
# define ERROR_MSG_KILL			"Error: kill"

int	error_exit(const char *error_message);

#endif

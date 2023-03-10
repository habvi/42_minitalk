#ifndef MINITALK_H
# define MINITALK_H

# define ERROR -1

// server.c
# define ERROR_WRITE		"Error: function write"
# define ERROR_SIGACTION	"Error: sigaction"
# define ERROR_KILL			"Error: kill"

// client.c
# define ERROR_ARGS			"Error: invalid args"

int	error_exit(const char *error_message);

#endif

#ifndef MINITALK_H
# define MINITALK_H

# define ERROR                  -1
# define ERROR_MSG_WRITE		"Error: function write"

// server.c
# define ERROR_MSG_SIGACTION	"Error: sigaction"

// client.c
# define MSG_USAGE              "usage: ./client <PID> <message>"
# define MSG_SEND_PID           "send message to pid:"
# define ERROR_MSG_ARGS			"Error: invalid args"
# define ERROR_MSG_PID			"Error: invalid pid"
# define ERROR_MSG_KILL			"Error: kill"

// error.c
int	error_exit(const char *error_message);

#endif

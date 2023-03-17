#ifndef ERROR_H
# define ERROR_H

// to do: not error
# define MSG_SERVER_PID			"> server pid:"
# define MSG_CLIENT_PID			"> client pid:"

# define ERROR					-1

# define ERROR_MSG_SIGACTION	"sigaction"
# define ERROR_MSG_KILL			"kill"
# define ERROR_MSG_WRITE		"write"

typedef enum e_error_code {
	ERROR_SIGACTION = 1,
	ERROR_KILL = 2,
	ERROR_WRITE_M = 3,
}	t_error_code;

#endif

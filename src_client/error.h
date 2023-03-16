#ifndef ERROR_H
# define ERROR_H

# define MSG_USAGE				"usage: ./client <PID> <message>"
# define MSG_SEND_PID			"send message to pid:"
# define MSG_RECIEVED			"recieved message from server!"

# define ERROR					-1

# define ERROR_MSG_ARGS			"invalid args"
# define ERROR_MSG_PID			"invalid pid"
# define ERROR_MSG_SIGACTION	"sigaction"
# define ERROR_MSG_KILL			"kill"
# define ERROR_MSG_WRITE		"write"

typedef enum e_error_code {
	INVALID_ARGS = 1,
	INVALID_PID = 2,
	ERROR_SIGACTION = 3,
	ERROR_KILL = 4,
	ERROR_WRITE_M = 5,
}	t_error_code;

#endif

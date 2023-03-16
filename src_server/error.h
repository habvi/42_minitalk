#ifndef ERROR_H
# define ERROR_H

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

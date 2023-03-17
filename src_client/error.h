#ifndef ERROR_H
# define ERROR_H

# define ERROR					-1

# define ERROR_MSG_ARGS			"invalid args"
# define ERROR_MSG_PID			"invalid pid"
# define ERROR_MSG_SIGACTION	"sigaction"
# define ERROR_MSG_KILL			"kill()"
# define ERROR_MSG_WRITE		"write()"

typedef enum e_error_code	t_error_code;

typedef enum e_error_code {
	INVALID_ARGS = 1,
	INVALID_PID = 2,
	ERROR_SIGACTION = 3,
	ERROR_KILL = 4,
	ERROR_WRITE = 5,
}	t_error_code;

void	error_exit(const t_error_code error_code);

#endif

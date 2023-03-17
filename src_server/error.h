#ifndef ERROR_H
# define ERROR_H

# define ERROR					-1

# define ERROR_MSG_ARGS			"invalid args"
# define ERROR_MSG_SIGACTION	"sigaction"
# define ERROR_MSG_KILL			"kill()"
# define ERROR_MSG_WRITE		"write()"

typedef enum e_error_code {
	INVALID_ARGS = 1,
	ERROR_SIGACTION = 2,
	ERROR_KILL = 3,
	ERROR_WRITE_M = 4,
}	t_error_code;

void	error_exit(const t_error_code error_code);

#endif

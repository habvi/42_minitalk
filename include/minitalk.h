#ifndef MINITALK_H
# define MINITALK_H

# define ERROR                  -1
# define ERROR_MSG_WRITE		"Error: function write"
# define ERROR_MSG_SIGACTION	"Error: sigaction"

// error.c
int		error_exit(const char *error_message);

// put_stderr.c
// void	put_str_to_stderr(const char *str);
// void	put_int_to_stderr(const int num);
void	put_str_int_to_stderr(const char *str, const int num);

#endif

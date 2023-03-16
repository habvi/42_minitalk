#ifndef SERVER_H
# define SERVER_H

# include <signal.h> // to do

typedef enum e_error_code	t_error_code;

typedef struct s_signal
{
	volatile sig_atomic_t	signum;
	volatile sig_atomic_t	client_pid;
}	t_signal;

// error.c
void	error_exit(const t_error_code error_code);

// put_stderr.c
// void	put_str_to_stderr(const char *str);
// void	put_int_to_stderr(const int num);
void	put_str_int_to_stderr(const char *str, const int num);

#endif

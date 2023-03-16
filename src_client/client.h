#ifndef CLIENT_H
# define CLIENT_H

# define ERROR	-1

typedef struct s_pid
{
	volatile sig_atomic_t	server_pid;
	volatile sig_atomic_t   is_correct_server_pid;
}	t_pid;

typedef enum e_error_code	t_error_code;

// error.c
void	error_exit(const t_error_code error_code);

// put_stderr.c
// void	put_str_to_stderr(const char *str);
// void	put_int_to_stderr(const int num);
void	put_str_int_to_stderr(const char *str, const int num);

#endif

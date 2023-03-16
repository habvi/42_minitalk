#ifndef CLIENT_H
# define CLIENT_H

# include <signal.h> // to do
# include <stdbool.h>

typedef enum e_error_code	t_error_code;

typedef struct s_pid
{
	volatile sig_atomic_t	server_pid;
	volatile sig_atomic_t	is_correct_server_pid;
}	t_pid;

// error.c
void	error_exit(const t_error_code error_code);

// args.c
bool	is_valid_args(const int argc, t_error_code *error_code);
bool	is_valid_pid(const char *arg, pid_t *pid, t_error_code *error_code);

// signal.c
void	signal_handler(int signum, siginfo_t *info, void *context);
bool	set_sigaction(struct sigaction *sa, t_error_code *error_code);

// send.c
bool	send_message(\
		const pid_t server_pid, const char *message, t_error_code *error_code);

// put.c
void	put_str_to_stderr(const char *str);
void	put_stderr(const char *str, const int num);
bool	put_usage(t_error_code *error_code);
bool	put_server_pid(const pid_t server_pid, t_error_code *error_code);
bool	put_recieved_message(t_error_code *error_code);

// recieve.c
bool	recieve_end_signal(t_error_code *error_code);

#endif
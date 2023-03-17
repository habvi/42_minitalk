#ifndef CLIENT_H
# define CLIENT_H

# include <signal.h> // to do
# include <stdbool.h>

# ifndef SLEEP_TIME
#  define SLEEP_TIME	150
# endif

typedef enum e_error_code	t_error_code;

typedef struct s_pid
{
	volatile sig_atomic_t	server_pid;
	volatile sig_atomic_t	is_correct_server_pid;
}	t_pid;

// args.c
bool	is_valid_args(const int argc, t_error_code *error_code);
bool	is_valid_pid(const char *arg, t_error_code *error_code);

// client.c, client_bonus.c
t_pid	get_g_pid(void);
void	set_g_server_pid(sig_atomic_t server_pid);
void	set_g_is_correct_server_pid(sig_atomic_t is_correct_server_pid);

// recieve.c
bool	recieve_end_signal(t_error_code *error_code);

// send.c
bool	send_message(const char *message, t_error_code *error_code);

// signal.c
void	signal_handler(int signum, siginfo_t *info, void *context);
bool	set_sigaction(struct sigaction *sa, t_error_code *error_code);

#endif

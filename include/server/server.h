#ifndef SERVER_H
# define SERVER_H

# include <signal.h>
# include <stdbool.h>

// both client and server
# ifndef SLEEP_TIME
#  define SLEEP_TIME	150
# endif

typedef enum e_error_code	t_error_code;

typedef struct s_signal
{
	sig_atomic_t	signum;
	sig_atomic_t	client_pid;
}	t_signal;

// args.c
bool		is_valid_args(const int argc, t_error_code *error_code);

// server.c, server_bonus.c
t_signal	get_g_signal(void);
void		set_g_signum(sig_atomic_t signum);
void		set_g_client_pid(sig_atomic_t client_pid);

// receive.c
bool		receive_message(t_error_code *error_code);

// signal.c
bool		set_sigaction(struct sigaction *sa, t_error_code *error_code);

#endif

#ifndef CLIENT_H
# define CLIENT_H

# include <signal.h>
# include <stdbool.h>

// both client and server
# ifndef SLEEP_TIME
#  define SLEEP_TIME	150
# endif

typedef enum e_error_code	t_error_code;

typedef struct s_pid
{
	sig_atomic_t	server_pid;
	sig_atomic_t	is_correct_server_pid;
}	t_pid;

// client.c, client_bonus.c
t_pid	get_g_pid(void);
void	set_g_server_pid(sig_atomic_t server_pid);
void	set_g_is_correct_server_pid(sig_atomic_t is_correct_server_pid);

// receive.c
bool	receive_end_signal(t_error_code *error_code);

// send.c
bool	send_message(const char *message, t_error_code *error_code);

// signal.c
void	signal_handler(int signum, siginfo_t *info, void *context);
bool	set_sigaction(struct sigaction *sa, t_error_code *error_code);

#endif

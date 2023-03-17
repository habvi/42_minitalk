#ifndef SERVER_H
# define SERVER_H

# include <signal.h> // to do
# include <stdbool.h>

typedef enum e_error_code	t_error_code;

typedef struct s_signal
{
	volatile sig_atomic_t	signum;
	volatile sig_atomic_t	client_pid;
}	t_signal;

// server.c
t_signal	get_g_signal(void);
void		set_g_signum(sig_atomic_t signum);
void		set_g_client_pid(sig_atomic_t client_pid);

// error.c
void		error_exit(const t_error_code error_code);

// put.c
bool		put_server_pid(t_error_code *error_code);
bool		put_client_pid(t_error_code *error_code);
bool		put_byte(const unsigned char byte, t_error_code *error_code);
void		put_error(const char *message);

// recieve.c
bool		recieve_message(t_error_code *error_code);

// signal.c
bool		set_sigaction(struct sigaction *sa, t_error_code *error_code);

#endif

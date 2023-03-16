#ifndef SERVER_H
# define SERVER_H

typedef struct s_signal
{
	volatile sig_atomic_t	signum;
	volatile sig_atomic_t	client_pid;
}	t_signal;

#endif

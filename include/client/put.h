#ifndef PUT_H
# define PUT_H

# include <stdbool.h>

# define MSG_USAGE      "> Usage: ./client <PID> <message>"
# define MSG_SEND_PID   "> send to server pid:"
# define MSG_RECIEVED   "> recieved all messages from server!"

typedef enum e_error_code	t_error_code;

bool	put_usage(t_error_code *error_code);
bool	put_server_pid(t_error_code *error_code);
bool	put_recieved_message(t_error_code *error_code);
void	put_error(const char *message);

#endif

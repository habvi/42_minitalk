#ifndef PUT_H
# define PUT_H

# include <stdbool.h>

# define MSG_USAGE		"> Usage: ./server"
# define MSG_SERVER_PID	"> server pid:"
# define MSG_CLIENT_PID	"> send back to client pid:"

typedef enum e_error_code	t_error_code;

bool	put_usage(t_error_code *error_code);
bool	put_server_pid(t_error_code *error_code);
bool	put_client_pid(t_error_code *error_code);
bool	put_byte(const unsigned char byte, t_error_code *error_code);
void	put_error(const char *message);

#endif

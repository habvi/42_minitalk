#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // getpid
#include <signal.h>

// SIGINT: 2 ctrl+C, SIGQUIT: 3 ctrl+\(￥)
// non-async-signal-safe
void signal_handler(int signum)
{
	static int count = 0;

	if (signum == SIGINT)
	{
		count++;
		printf("caught SIGINT [%d]\n", count);
		return;
	}
	printf("caught SIGQUIT\n");
	exit(EXIT_SUCCESS);
}

int main(void)
{
	printf("receiver pid %d\n", getpid());

	// success: previous signal dispodition, error: SIG_ERR(-1)
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGQUIT, signal_handler) == SIG_ERR)
		exit(EXIT_FAILURE);
	for (int j = 0; ; j++)
	{
		printf("%d\n", j);
		sleep(2);
	}
	return 0;
}

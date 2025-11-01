#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void	do_nothing(int sig)
{
	(void)sig;
}

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		f();
		exit(0);
	}
	if (pid > 0)
	{
		struct sigaction sa = {0};
		sa.sa_handler = do_nothing;
		if (sigaction(SIGALRM, &sa, NULL) < 0)
			return (-1);
		alarm(timeout);
		pid_t r = waitpid(pid, &status, 0);
		alarm(0);
		if (r < 0)
		{
			if (errno == EINTR)
			{
				kill(pid, SIGKILL);
				waitpid(pid, &status, 0);
				if (verbose)
					printf("Bad function: timed out after %u seconds\n",
						timeout);
				return (0);
			}
		}
		if (WIFEXITED(status))
		{
			int exit_code = WEXITSTATUS(status);
			if (exit_code == 0)
			{
				if (verbose)
					printf("Nice function!\n");
				return (1);
			}
			else
			{
				if (verbose)
					printf("Bad function: exited with code %d\n", exit_code);
				return (0);
			}
		}
		if (WIFSIGNALED(status))
		{
			int sig = WTERMSIG(status);
			if (verbose)
				printf("Bad function: %s\n", strsignal(sig));
			return (0);
		}
	}
	return (-1);
}

// 1. Fonction gentille
void	nice_function(void)
{
	printf("Hello from nice function!\n");
	// Termine normalement
}

// 2. Fonction qui fait une boucle infinie (timeout)
void	infinite_loop(void)
{
	printf("Starting infinite loop...\n");
	while (1)
	{
		// Boucle infinie
	}
}

// 3. Fonction qui exit avec un code d'erreur
void	bad_exit(void)
{
	printf("Exiting with code 42...\n");
	exit(42);
}

// 4. Fonction qui fait un segfault
void	segfault_function(void)
{
	int	*p;

	printf("About to segfault...\n");
	p = NULL;
	*p = 42; // BOOM!
}

// 5. Fonction qui fait abort()
void	abort_function(void)
{
	printf("About to abort...\n");
	abort();
}

// 6. Fonction qui prend du temps mais finit bien
void	slow_function(void)
{
	printf("Sleeping 1 second...\n");
	sleep(1);
	printf("Done!\n");
}

void	annoying_function(void)
{
	printf("get ready to suffer\n");
	signal(SIGALRM, SIG_IGN);
	while (1)
	{
		sleep(1);
	}
}

// ========== MAIN ==========

int	main(void)
{
	int	r1;
	int	r2;
	int	r3;
	int	r4;
	int	r5;
	int	r6;
	int	r7;

	printf("========== TEST SANDBOX ==========\n\n");
	printf("Test 1: Nice function\n");
	printf("Expected: Nice function! return (1)\n");
	r1 = sandbox(nice_function, 3, true);
	printf("Returned: %d\n\n", r1);
	printf("---\n\n");
	printf("Test 2: Infinite loop (timeout)\n");
	printf("Expected: Bad function: timed out after 2 seconds return (0)\n");
	r2 = sandbox(infinite_loop, 2, true);
	printf("Returned: %d\n\n", r2);
	printf("---\n\n");
	printf("Test 3: Bad exit code\n");
	printf("Expected: Bad function: exited with code 42 return (0)\n");
	r3 = sandbox(bad_exit, 3, true);
	printf("Returned: %d\n\n", r3);
	printf("---\n\n");
	printf("Test 4: Segmentation fault\n");
	printf("Expected: Bad function: Segmentation fault return (0)\n");
	r4 = sandbox(segfault_function, 3, true);
	printf("Returned: %d\n\n", r4);
	printf("---\n\n");
	printf("Test 5: Abort\n");
	printf("Expected: Bad function: Aborted return (0)\n");
	r5 = sandbox(abort_function, 3, true);
	printf("Returned: %d\n\n", r5);
	printf("---\n\n");
	printf("Test 6: Slow but nice function\n");
	printf("Expected: Nice function! return (1)\n");
	r6 = sandbox(slow_function, 3, true);
	printf("Returned: %d\n\n", r6);
	printf("---\n\n");
	printf("Test 7: Test annul signal\n");
	printf("Expected: Bad function: timed out after 3 seconds return (0)\n");
	r7 = sandbox(annoying_function, 3, true);
	printf("Returned: %d\n\n", r7);
	printf("========== FIN DES TESTS ==========\n");
	return (0);
}

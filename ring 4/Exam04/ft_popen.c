
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <string.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
	if (!argv || !file || (type != 'r' && type != 'w')) // ← Corrigé
		return (-1);
	int fd[2];
	if (pipe(fd) < 0)
		return (-1);
	pid_t pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		if (type == 'r')
		{
			close(fd[0]);
			if (dup2(fd[1], 1) < 0)
				exit(-1); // ← exit au lieu de return dans l'enfant
			close(fd[1]);
		}
		if (type == 'w')
		{
			close(fd[1]);
			if (dup2(fd[0], 0) < 0)
				exit(-1);
			close(fd[0]);
		}
		execvp(file, argv); // ← Corrigé (execvp, pas exevp)
		exit(-1);
	}
	else
	{
		if (type == 'r')
		{
			close(fd[1]);
			return (fd[0]);
		}
		if (type == 'w')
		{
			close(fd[0]);
			return (fd[1]);
		}
	}
	return (-1); // ← Sécurité (ne devrait jamais arriver)
}


int main()
{
    // Test type 'w' : envoyer des données à cat
    int fd = ft_popen("cat", (char *const[]){"cat", NULL}, 'w');
    if (fd < 0)
    {
        printf("Erreur ft_popen\n");
        return 1;
    }
    
    char *msg1 = "Hello from parent!\n";
    char *msg2 = "Ceci est un test.\n";
    
    write(fd, msg1, strlen(msg1));
    write(fd, msg2, strlen(msg2));
    
    close(fd);  // Important : signale la fin à cat
    sleep(1);   // Laisse le temps à cat d'afficher
    
    return 0;
}
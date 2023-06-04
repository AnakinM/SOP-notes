#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

void handle_sigusr2(int sig) {
    printf("Otrzymałem sygnał SIGUSR2 od innego procesu\n");
}

int main() {
    printf("ID Procesu: %d\n", getpid());
    printf("ID Procesu rodzica: %d\n", getppid());
    printf("ID rzeczywiste uzytkownika: %d\n", getuid());
    printf("ID efektywne uzytkownika: %d\n", geteuid());
    printf("ID rzeczywiste grupy: %d\n", getgid());
    printf("ID efektywne grupy: %d\n", getegid());

    pid_t pid = fork();

    if (pid < 0) {
        printf("Błąd podczas tworzenia procesu potomnego\n");
        exit(1);
    }

    if (pid == 0) {
        printf("Jestem procesem potomnym\n");
        printf("Mój PID: %d\n", getpid());
        printf("PID mojego rodzica: %d\n", getppid());
        kill(getppid(), SIGUSR2);
        sleep(5);
    }
    else {
        printf("Jestem procesem macierzystym\n");
        printf("Mój PID: %d\n", getpid());
        printf("PID mojego potomka: %d\n", pid);

        if (signal(SIGUSR2, handle_sigusr2) == SIG_ERR) {
            printf("Funkcja signal ma problem z SIGUSR2\n");
        }

        sleep(15);
        printf("Naciśnij dowolny klawisz, aby kontynuować...\n");
        getchar();
    }

    return 0;
}

/*
Napisz program, ktory w kolejnych liniach (w układzie OPIS: WARTOŚĆ) wypisuje informacje:
- ID Procesu
- ID Procesu rodzica
- ID rzeczywiste uzytkownika
- ID efektywne uzytkownika
- ID rzeczywiste grupy
- ID efektywne grupy

Następnie powoła proces potomny, ktory:
- Wyświetli informacje ze jest procesem potomnym
- wyswietli swoj PID
- wyswietli PID swojego rodzica
- Wysle sygnal SIGUSR2 do swojego rodzica
- Zaczeka 5 sekund

Jako proces macierzysty:
- Wyswietli informacje ze jest procesem macierzystym
- wyswietli swoj PID
- wyswietli PID swojego potomka
- odbierze sygnal SIGUSR2 od swojego potomka i obsłuy go wyświetlając informację:
    "Otrzymałem sygnał SIGUSR2 od innego procesu"
    a w przypadku błędu: "Funkcja signal ma problem z SIGUSR2"
- Zaczeka 15 sekund
- poprosi o naciśnięcie klawisza eby kontynuować
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int sig_no)
{
    if (sig_no == SIGUSR2)
    {
        printf("Otrzymałem sygnał SIGUSR2 od innego procesu\n");
    }
    else
    {
        printf("Funkcja signal ma problem z SIGUSR2\n");
    }
}

int main()
{
    printf("ID Procesu: %d\n", getpid());
    printf("ID Procesu rodzica: %d\n", getppid());
    printf("ID rzeczywiste uzytkownika: %d\n", getuid());
    printf("ID efektywne uzytkownika: %d\n", geteuid());
    printf("ID rzeczywiste grupy: %d\n", getgid());
    printf("ID efektywne grupy: %d\n", getegid());

    pid_t pid = fork();

    if (pid == 0)
    {
        printf("Jestem procesem potomnym\n");
        printf("PID: %d\n", getpid());
        printf("PID rodzica: %d\n", getppid());
        kill(getppid(), SIGUSR2);
        sleep(5);
    }
    else if (pid > 0)
    {
        printf("Jestem procesem macierzystym\n");
        printf("PID: %d\n", getpid());
        printf("PID potomka: %d\n", pid);
        signal(SIGUSR2, signal_handler);
        sleep(15);
        printf("Nacisnij dowolny klawisz aby kontynuowac\n");
        getchar();
    }
    else
    {
        printf("Funkcja fork ma problem\n");
    }

    return 0;
}
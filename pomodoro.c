#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define RED   "\033[0;31m"
#define GREEN "\033[0;32m"
#define CYAN  "\033[0;36m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"


void print_banner(void)
{
    printf(CYAN "\n");
    printf("╔══════════════════════════════════════════╗\n");
    printf("║                                          ║\n");
    printf("║        🕑   P O M O D O R O   C L I      ║\n");
    printf("║          by 42 Student  •  v1.0          ║\n");
    printf("║                                          ║\n");
    printf("╚══════════════════════════════════════════╝\n");
    printf(RESET "\n");
}

void log_session(const char *label)
{
    FILE *f = fopen("pomodoro.log", "a");
    if (!f)
    {
        perror("Error opening pomodoro.log");
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    fprintf(f, "[%02d/%02d/%d %02d:%02d:%02d] Session %s terminée\n",
        t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
        t->tm_hour, t->tm_min, t->tm_sec, label);
    fclose(f);
}

void start_timer(int time_left, const char *label, const char *color)
{
    int minutes, seconds;

    printf("\n--- %s%s session%s ---\n", color, label, RESET);
    while (time_left >= 0)
    {
        minutes = time_left / 60;
        seconds = time_left % 60;
        printf("\r%s[%s] %02d:%02d restantes%s", color, label, minutes, seconds, RESET);
        fflush(stdout);
        sleep(1);
        time_left--;
    }
    printf("\r%sTimer terminé !%s\n", color, RESET);
    log_session(label);
    printf("📝 %sSession %s enregistrée dans le log.%s\n", CYAN, label, RESET);
}

void start_focus(int minutes)
{
    start_timer(minutes * 60, "FOCUS", RED);
    printf("%s🧠 Focus terminé ! Prends une pause.%s\n", YELLOW, RESET);
}

void start_pause(int minutes)
{
    start_timer(minutes * 60, "PAUSE", GREEN);
    printf("%s✅ Pause terminée ! Prêt pour une nouvelle session ?%s\n", YELLOW, RESET);
}

void show_log(void)
{
    FILE *f = fopen("pomodoro.log", "r");
    if (!f)
    {
        printf("%sAucun log trouvé.%s\n", YELLOW, RESET);
        return;
    }

    char line[256];
    printf("%s----- Historique des sessions ----- %s\n", CYAN, RESET);
    while (fgets(line, sizeof(line), f))
        printf("%s", line);
    fclose(f);
    printf("%s-----------------------------------%s\n", CYAN, RESET);
}

void show_help(void)
{
    printf("%sUsage:%s ./pomodoro [command] [options]\n", CYAN, RESET);
    printf("%sCommands:%s\n", CYAN, RESET);
    printf("  start   Start a pomodoro cycle\n");
    printf("  log     Show session history\n");
    printf("  help    Show this help message\n\n");
    printf("%sOptions (with 'start'):%s\n", CYAN, RESET);
    printf("  --focus <minutes>   Duration of focus time (default 25)\n");
    printf("  --pause <minutes>   Duration of break time (default 5)\n");
    printf("  --repeat <number>   Number of cycles (default 1)\n");
}


int main(int argc, char **argv)
{
    print_banner();
    
    if (argc < 2)
    {
        printf("%sUsage:%s ./pomodoro [start | log | help]\n", CYAN, RESET);
        return 1;
    }

    if (strcmp(argv[1], "help") == 0)
    {
        show_help();
        return 0;
    }

    if (strcmp(argv[1], "log") == 0)
    {
        show_log();
        return 0;
    }

    if (strcmp(argv[1], "start") == 0)
    {
        int focus = 25;
        int pause = 5;
        int repeat = 1;


        for (int i = 2; i < argc; i++)
        {
            if (strcmp(argv[i], "--focus") == 0 && i + 1 < argc)
                focus = atoi(argv[++i]);
            else if (strcmp(argv[i], "--pause") == 0 && i + 1 < argc)
                pause = atoi(argv[++i]);
            else if (strcmp(argv[i], "--repeat") == 0 && i + 1 < argc)
                repeat = atoi(argv[++i]);
        }


        for (int i = 1; i <= repeat; i++)
        {
            printf("\n%s=== Cycle %d/%d ===%s\n", CYAN, i, repeat, RESET);
            start_focus(focus);
            if (i < repeat)
                start_pause(pause);
        }

        printf("\n%s🏁 Tous les cycles sont terminés ! Bravo !%s\n", GREEN, RESET);
        return 0;
    }

    printf("%sCommande inconnue.%s Utilise './pomodoro help'\n", RED, RESET);
    return 1;
}

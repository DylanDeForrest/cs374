#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/select.h>

#define SPEED_MIN 0

static volatile sig_atomic_t speed = 0;

static void handle_usr1(int s)
{
    (void)s;
    if (speed > SPEED_MIN)
        speed--;
    printf("decrease speed to: %d\n", speed);
}

static void handle_usr2(int s)
{
    (void)s;
    speed++;
    printf("increase speed to: %d\n", speed);
}

int main(void)
{
    printf("PID=%d\n", (int)getpid());
    fflush(stdout);

    struct sigaction sa;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = handle_usr1;
    sigaction(SIGUSR1, &sa, NULL);
    sa.sa_handler = handle_usr2;
    sigaction(SIGUSR2, &sa, NULL);

    sigset_t block, orig;
    sigemptyset(&block);
    sigaddset(&block, SIGUSR1);
    sigaddset(&block, SIGUSR2);
    sigprocmask(SIG_BLOCK, &block, &orig);

    for (;;) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        pselect(STDIN_FILENO + 1, &fds, NULL, NULL, NULL, &orig);

        if (!FD_ISSET(STDIN_FILENO, &fds))
            continue;

        char buf[256];
        ssize_t n = read(STDIN_FILENO, buf, sizeof(buf));
        if (n <= 0)
            break;

            for (ssize_t i = 0; i < n; i++) {
            if (buf[i] == '+') {
                speed++;
                printf("increase speed to: %d\n", speed);
            } else if (buf[i] == '-') {
                if (speed > SPEED_MIN)
                    speed--;
                printf("decrease speed to: %d\n", speed);
            } else if (buf[i] == 'q') {
                return 0;
            }
        }
    }

    return 0;
}
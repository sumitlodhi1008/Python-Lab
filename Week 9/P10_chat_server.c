#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

int client_sockets[MAX_CLIENTS];
int client_count = 0;

void broadcast(char *msg, int sender_fd) {
    int i;
    for (i = 0; i < client_count; i++) {
        if (client_sockets[i] != sender_fd) {
            write(client_sockets[i], msg, strlen(msg));
        }
    }
}

void handle_client(int client_fd, int index) {
    char buffer[BUFFER_SIZE];
    char msg[BUFFER_SIZE + 50];
    int n;

    sprintf(msg, "Client %d joined the chat\n", index + 1);
    printf("%s", msg);
    broadcast(msg, client_fd);

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        n = read(client_fd, buffer, BUFFER_SIZE - 1);
        if (n <= 0) {
            sprintf(msg, "Client %d left the chat\n", index + 1);
            printf("%s", msg);
            broadcast(msg, client_fd);
            close(client_fd);
            exit(0);
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        sprintf(msg, "Client %d: %s\n", index + 1, buffer);
        printf("%s", msg);
        broadcast(msg, client_fd);
    }
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    pid_t pid;

    signal(SIGCHLD, SIG_IGN);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(1);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(1);
    }

    listen(server_fd, MAX_CLIENTS);
    printf("Chat Server started on port %d\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        if (client_count >= MAX_CLIENTS) {
            char *msg = "Server full\n";
            write(client_fd, msg, strlen(msg));
            close(client_fd);
            continue;
        }

        client_sockets[client_count] = client_fd;

        pid = fork();
        if (pid == 0) {
            close(server_fd);
            handle_client(client_fd, client_count);
        } else {
            client_count++;
        }
    }

    close(server_fd);
    return 0;
}

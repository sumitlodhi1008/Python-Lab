#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int sock;

void *receive_handler(void *arg) {
    char buffer[BUFFER_SIZE];
    int n;
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        n = read(sock, buffer, BUFFER_SIZE - 1);
        if (n <= 0) {
            printf("Disconnected from server\n");
            exit(0);
        }
        printf("%s", buffer);
    }
    return NULL;
}

int main() {
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    pthread_t recv_thread;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        exit(1);
    }

    printf("Connected to chat server\n");
    printf("Start typing messages:\n");

    pthread_create(&recv_thread, NULL, receive_handler, NULL);

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        fgets(buffer, BUFFER_SIZE, stdin);
        if (strcmp(buffer, "exit\n") == 0) {
            break;
        }
        write(sock, buffer, strlen(buffer));
    }

    close(sock);
    return 0;
}

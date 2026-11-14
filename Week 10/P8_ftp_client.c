#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 4096

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char command[BUFFER_SIZE];

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

    printf("Connected to FTP Server.\n");
    printf("Commands: LIST, GET <filename>, QUIT\n");

    while (1) {
        printf("ftp> ");
        fgets(command, BUFFER_SIZE, stdin);
        command[strcspn(command, "\r\n")] = 0;

        send(sock, command, strlen(command), 0);

        if (strcmp(command, "QUIT") == 0) {
            memset(buffer, 0, BUFFER_SIZE);
            recv(sock, buffer, BUFFER_SIZE - 1, 0);
            printf("%s", buffer);
            break;
        }

        if (strncmp(command, "GET ", 4) == 0) {
            char *filename = command + 4;
            FILE *fp = fopen(filename, "wb");
            if (fp == NULL) {
                printf("Cannot create local file.\n");
                continue;
            }
            memset(buffer, 0, BUFFER_SIZE);
            int n = recv(sock, buffer, BUFFER_SIZE - 1, 0);
            if (n > 0) {
                if (strncmp(buffer, "ERROR:", 6) == 0) {
                    printf("%s", buffer);
                    fclose(fp);
                    remove(filename);
                } else {
                    fwrite(buffer, 1, n, fp);
                    fclose(fp);
                    printf("File '%s' downloaded successfully.\n", filename);
                }
            }
        }
        else {
            memset(buffer, 0, BUFFER_SIZE);
            int n = recv(sock, buffer, BUFFER_SIZE - 1, 0);
            if (n > 0) {
                printf("%s", buffer);
            }
        }
    }

    close(sock);
    return 0;
}

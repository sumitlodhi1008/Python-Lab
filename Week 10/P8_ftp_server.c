#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <dirent.h>

#define PORT 8080
#define BUFFER_SIZE 4096

void handle_client(int client_fd) {
    char buffer[BUFFER_SIZE];
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int n = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
        if (n <= 0)
            break;

        buffer[strcspn(buffer, "\r\n")] = 0;

        if (strcmp(buffer, "LIST") == 0) {
            char file_list[BUFFER_SIZE] = "";
            DIR *d = opendir(".");
            struct dirent *entry;
            while ((entry = readdir(d)) != NULL) {
                if (entry->d_type == DT_REG) {
                    strcat(file_list, entry->d_name);
                    strcat(file_list, "\n");
                }
            }
            closedir(d);
            if (strlen(file_list) == 0)
                strcpy(file_list, "No files found.\n");
            send(client_fd, file_list, strlen(file_list), 0);
        }
        else if (strncmp(buffer, "GET ", 4) == 0) {
            char *filename = buffer + 4;
            FILE *fp = fopen(filename, "rb");
            if (fp == NULL) {
                char *msg = "ERROR: File not found.\n";
                send(client_fd, msg, strlen(msg), 0);
            } else {
                char file_buf[BUFFER_SIZE];
                int bytes;
                while ((bytes = fread(file_buf, 1, BUFFER_SIZE, fp)) > 0) {
                    send(client_fd, file_buf, bytes, 0);
                }
                fclose(fp);
            }
        }
        else if (strcmp(buffer, "QUIT") == 0) {
            char *msg = "Goodbye.\n";
            send(client_fd, msg, strlen(msg), 0);
            break;
        }
        else {
            char *msg = "ERROR: Unknown command. Use LIST, GET <filename>, or QUIT.\n";
            send(client_fd, msg, strlen(msg), 0);
        }
    }
    close(client_fd);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

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

    if (listen(server_fd, 5) < 0) {
        perror("listen");
        exit(1);
    }

    printf("FTP Server running on port %d\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }
        printf("Client connected.\n");
        handle_client(client_fd);
        printf("Client disconnected.\n");
    }

    close(server_fd);
    return 0;
}

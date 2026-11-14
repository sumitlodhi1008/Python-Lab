#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9090
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    struct hostent *host;
    struct in_addr **addr_list;

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

    listen(server_fd, 5);
    printf("DNS Resolver Server running on port %d\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        memset(buffer, 0, BUFFER_SIZE);
        int n = read(client_fd, buffer, BUFFER_SIZE - 1);
        if (n <= 0) {
            close(client_fd);
            continue;
        }

        buffer[strcspn(buffer, "\n")] = '\0';
        printf("Resolving domain: %s\n", buffer);

        host = gethostbyname(buffer);
        if (host == NULL) {
            char *msg = "Error: Could not resolve domain\n";
            write(client_fd, msg, strlen(msg));
        } else {
            char response[BUFFER_SIZE];
            memset(response, 0, BUFFER_SIZE);
            sprintf(response, "Domain: %s\n", buffer);
            addr_list = (struct in_addr **)host->h_addr_list;
            int i;
            for (i = 0; addr_list[i] != NULL; i++) {
                char line[256];
                sprintf(line, "IP Address: %s\n", inet_ntoa(*addr_list[i]));
                strcat(response, line);
            }
            write(client_fd, response, strlen(response));
        }

        close(client_fd);
    }

    close(server_fd);
    return 0;
}

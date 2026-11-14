#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define MAXLEN 1024

int main() {
    int sockfd;
    char buffer[MAXLEN];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    printf("UDP Server running on port %d\n", PORT);

    while (1) {
        len = sizeof(cliaddr);
        memset(buffer, 0, MAXLEN);
        recvfrom(sockfd, buffer, MAXLEN, 0, (struct sockaddr *)&cliaddr, &len);
        printf("Client: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0)
            break;

        printf("Server: ");
        memset(buffer, 0, MAXLEN);
        fgets(buffer, MAXLEN, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&cliaddr, len);
    }

    close(sockfd);
    return 0;
}

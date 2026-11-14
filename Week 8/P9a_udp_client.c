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
    struct sockaddr_in servaddr;
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("UDP Client started. Type messages (type 'exit' to quit):\n");

    while (1) {
        printf("Client: ");
        memset(buffer, 0, MAXLEN);
        fgets(buffer, MAXLEN, stdin);
        buffer[strlen(buffer) - 1] = '\0';

        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

        if (strcmp(buffer, "exit") == 0)
            break;

        len = sizeof(servaddr);
        memset(buffer, 0, MAXLEN);
        recvfrom(sockfd, buffer, MAXLEN, 0, (struct sockaddr *)&servaddr, &len);
        printf("Server: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9090
#define MAXLEN 1024

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[MAXLEN];
    FILE *fp;
    int bytes;
    char filename[256];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Connected to server.\n");

    printf("Enter filename to send: ");
    scanf("%s", filename);

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("File not found.\n");
        close(sockfd);
        return 1;
    }

    while ((bytes = fread(buffer, 1, MAXLEN, fp)) > 0) {
        send(sockfd, buffer, bytes, 0);
    }

    printf("File sent successfully.\n");

    fclose(fp);
    close(sockfd);
    return 0;
}

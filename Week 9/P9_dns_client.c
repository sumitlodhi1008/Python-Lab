#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9090
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char domain[256];
    char buffer[BUFFER_SIZE];

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

    printf("Enter domain name: ");
    fgets(domain, sizeof(domain), stdin);
    domain[strcspn(domain, "\n")] = '\0';

    write(sock, domain, strlen(domain));

    memset(buffer, 0, BUFFER_SIZE);
    int n = read(sock, buffer, BUFFER_SIZE - 1);
    if (n > 0) {
        printf("\nServer Response:\n%s", buffer);
    }

    printf("DNS Server Address: 127.0.0.1:%d\n", PORT);

    close(sock);
    return 0;
}
